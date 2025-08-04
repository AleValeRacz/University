using System.Data;
using HotelApp.Models;
using MySql.Data.MySqlClient;

namespace HotelApp.Services;

public class Service
{
    private readonly string connectionString;

    public Service(IConfiguration configuration)
    {
        connectionString = configuration.GetConnectionString("DefaultConnection");
    }

    public async Task<User> LogIn(string username, string password)
    {
        User user = null;
        using (MySqlConnection connection = new MySqlConnection(connectionString))
        {
            await connection.OpenAsync();

            string query = "SELECT id, username, password FROM users WHERE username = @username AND password = @password";

            using (MySqlCommand command = new MySqlCommand(query, connection))
            {
                command.Parameters.AddWithValue("@username", username);
                command.Parameters.AddWithValue("@password", password);

                using (MySqlDataReader reader = (MySqlDataReader) await command.ExecuteReaderAsync())
                {
                    if (await reader.ReadAsync())
                    {
                        user = new User
                        {
                            Id = reader.GetInt32("id"),
                            Username = reader.GetString("username"),
                            Password = reader.GetString("password")
                        };
                    }
                }
            }
        }

        return user;
    }


    public async Task<PaginationResponse> GetRoomsAsync(int page, int pageSize)
    {
        var rooms = new List<Room>();
        int totalRooms;

        using var conn = new MySqlConnection(connectionString);
        await conn.OpenAsync();

        using (var countCmd = new MySqlCommand("SELECT COUNT(*) FROM rooms", conn))
        {
            totalRooms = Convert.ToInt32(await countCmd.ExecuteScalarAsync());
        }

        var offset = (page - 1) * pageSize;
        using var cmd = new MySqlCommand("SELECT * FROM rooms LIMIT @limit OFFSET @offset", conn);
        cmd.Parameters.AddWithValue("@limit", pageSize);
        cmd.Parameters.AddWithValue("@offset", offset);

        using var reader = await cmd.ExecuteReaderAsync();
        while (await reader.ReadAsync())
        {
            rooms.Add(new Room
            {
                Id = reader.GetInt32("ID"),
                Type = reader.GetString("Type"),
                Price = reader.GetInt32("Price"),
                Hotel = reader.GetString("Hotel"),
                Number = reader.GetInt32("Number")
            });
        }

        return new PaginationResponse
        {
            Rooms = rooms,
            TotalPages = (int)Math.Ceiling((double)totalRooms / pageSize)
        };
    }

    public async Task<Room> GetRoomByIdAsync(int id)
    {
        using var conn = new MySqlConnection(connectionString);
        await conn.OpenAsync();

        using var cmd = new MySqlCommand("SELECT * FROM rooms WHERE ID = @id", conn);
        cmd.Parameters.AddWithValue("@id", id);

        using var reader = await cmd.ExecuteReaderAsync();
        if (await reader.ReadAsync())
        {
            return new Room
            {
                Id = reader.GetInt32("ID"),
                Type = reader.GetString("Type"),
                Price = reader.GetInt32("Price"),
                Hotel = reader.GetString("Hotel"),
                Number = reader.GetInt32("Number")
            };
        }
        return null;
    }

    public async Task<PaginationResponse> GetRoomsByFilterAsync(string column, object value, int page, int pageSize)
    {
        var rooms = new List<Room>();
        int totalRooms;

        var countQuery = $"SELECT COUNT(*) FROM rooms WHERE {column} = @val";
        var selectQuery = $"SELECT * FROM rooms WHERE {column} = @val LIMIT @limit OFFSET @offset";

        using var conn = new MySqlConnection(connectionString);
        await conn.OpenAsync();

        using (var countCmd = new MySqlCommand(countQuery, conn))
        {
            countCmd.Parameters.AddWithValue("@val", value);
            totalRooms = Convert.ToInt32(await countCmd.ExecuteScalarAsync());
        }

        var offset = (page - 1) * pageSize;
        using var cmd = new MySqlCommand(selectQuery, conn);
        cmd.Parameters.AddWithValue("@val", value);
        cmd.Parameters.AddWithValue("@limit", pageSize);
        cmd.Parameters.AddWithValue("@offset", offset);

        using var reader = await cmd.ExecuteReaderAsync();
        while (await reader.ReadAsync())
        {
            rooms.Add(new Room
            {
                Id = reader.GetInt32("ID"),
                Type = reader.GetString("Type"),
                Price = reader.GetInt32("Price"),
                Hotel = reader.GetString("Hotel"),
                Number = reader.GetInt32("Number")
            });
        }

        return new PaginationResponse
        {
            Rooms = rooms,
            TotalPages = (int)Math.Ceiling((double)totalRooms / pageSize)
        };
    }

    public async Task<List<Reservation>> GetUserReservationsAsync(int userId)
    {
        var reservations = new List<Reservation>();

        using var conn = new MySqlConnection(connectionString);
        await conn.OpenAsync();

        string query = @"
            SELECT r.ID, r.RoomID, r.StartDate, r.EndDate, r.UserID,
                   rm.Number AS RoomNumber, rm.Hotel
            FROM reservations r
            JOIN rooms rm ON r.RoomID = rm.ID
            WHERE r.UserID = @userId";

        using var cmd = new MySqlCommand(query, conn);
        cmd.Parameters.AddWithValue("@userId", userId);

        using var reader = await cmd.ExecuteReaderAsync();
        while (await reader.ReadAsync())
        {
            reservations.Add(new Reservation
            {
                Id = reader.GetInt32("ID"),
                StartDate = reader.GetDateTime("StartDate"),
                EndDate = reader.GetDateTime("EndDate"),
                UserID = reader.GetInt32("UserID"),
                RoomNumber = reader.GetInt32("RoomNumber"),
                Hotel = reader.GetString("Hotel")
            });
        }

        return reservations;
    }

    public async Task<Reservation> GetReservationByIdAsync(int id)
    {
        using var conn = new MySqlConnection(connectionString);
        await conn.OpenAsync();

        using var cmd = new MySqlCommand("SELECT * FROM reservations WHERE ID = @id", conn);
        cmd.Parameters.AddWithValue("@id", id);

        using var reader = await cmd.ExecuteReaderAsync();
        if (await reader.ReadAsync())
        {
            return new Reservation
            {
                Id = reader.GetInt32("ID"),
                StartDate = reader.GetDateTime("StartDate"),
                EndDate = reader.GetDateTime("EndDate"),
                UserID = reader.GetInt32("UserID")
            };
        }
        return null;
    }

    public async Task<bool> InsertReservationAsync(int roomId, DateTime start, DateTime end, int userId)
    {
        using var conn = new MySqlConnection(connectionString);
        await conn.OpenAsync();

        string query = "INSERT INTO reservations (RoomID, StartDate, EndDate, UserID) VALUES (@roomId, @start, @end, @userId)";
        using var cmd = new MySqlCommand(query, conn);
        cmd.Parameters.AddWithValue("@roomId", roomId);
        cmd.Parameters.AddWithValue("@start", start);
        cmd.Parameters.AddWithValue("@end", end);
        cmd.Parameters.AddWithValue("@userId", userId);

        return await cmd.ExecuteNonQueryAsync() > 0;
    }

    public async Task<bool> UpdateReservationAsync(int id, DateTime start, DateTime end)
    {
        using var conn = new MySqlConnection(connectionString);
        await conn.OpenAsync();

        string query = "UPDATE reservations SET StartDate = @start, EndDate = @end WHERE ID = @id";
        using var cmd = new MySqlCommand(query, conn);
        cmd.Parameters.AddWithValue("@start", start);
        cmd.Parameters.AddWithValue("@end", end);
        cmd.Parameters.AddWithValue("@id", id);

        return await cmd.ExecuteNonQueryAsync() > 0;
    }

    public async Task<bool> DeleteReservationAsync(int id)
    {
        using var conn = new MySqlConnection(connectionString);
        await conn.OpenAsync();

        string query = "DELETE FROM reservations WHERE ID = @id";
        using var cmd = new MySqlCommand(query, conn);
        cmd.Parameters.AddWithValue("@id", id);

        return await cmd.ExecuteNonQueryAsync() > 0;
    }

    public async Task<bool> DeleteAllReservationsByUser(int userID)
    {
        using var conn = new MySqlConnection(connectionString);
        await conn.OpenAsync();
        
        string query = "DELETE FROM reservations WHERE userID = @userId";
        using var cmd = new MySqlCommand(query, conn);
        cmd.Parameters.AddWithValue("@userId", userID);

        return await cmd.ExecuteNonQueryAsync() > 0;
    }

    public async Task<bool> CheckAvailabilityAsync(int roomId, DateTime start, DateTime end, int excludeId)
    {
        using var conn = new MySqlConnection(connectionString);
        await conn.OpenAsync();

        string query = @"
            SELECT count(*) FROM reservations
            WHERE RoomID = @roomId
            AND ID != @excludeId
            and not (EndDate < @start or StartDate > @end)";

        using var cmd = new MySqlCommand(query, conn);
        cmd.Parameters.AddWithValue("@roomId", roomId);
        cmd.Parameters.AddWithValue("@excludeId", excludeId);
        cmd.Parameters.AddWithValue("@start", start);
        cmd.Parameters.AddWithValue("@end", end);

        var count = Convert.ToInt32(await cmd.ExecuteScalarAsync());
        return count == 0;

    }


}

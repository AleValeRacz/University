using System.Data;
using ChannelsEx.Models;
using MySql.Data.MySqlClient;


namespace ChannelsEx.Services
{
    public class Service
    {

        private readonly string connectionString;

        public Service(IConfiguration configuration)
        {
            connectionString = configuration.GetConnectionString("DefaultConnection");
        }

        public async Task<Person> LogIn(string username)
        {
            Person user = null;
            using (MySqlConnection connection = new MySqlConnection(connectionString))
            {
                await connection.OpenAsync();

                string query = "SELECT id, name,age,gender FROM persons WHERE name = @name";

                using (MySqlCommand command = new MySqlCommand(query, connection))
                {
                    command.Parameters.AddWithValue("@name", username);

                    using (MySqlDataReader reader = (MySqlDataReader) await command.ExecuteReaderAsync())
                    {
                        if (await reader.ReadAsync())
                        {
                            user = new Person
                            {
                                Id = reader.GetInt32("id"),
                                Name = reader.GetString("name"),
                                Age = reader.GetInt32("age"),
                                Gender = reader.GetString("gender")
                            };
                        }
                    }
                }
            }

            return user;
        }

        public async Task<List<Channel>> GetChannelsByUser( string username)
        {
            var channels = new List<Channel>();
            
            using var conn = new MySqlConnection(connectionString);

            await conn.OpenAsync();

            string query = @"select c.* from channels c inner join persons p on p.id = c.ownerId where p.name = @name";
            using var cmd = new MySqlCommand(query, conn);
            cmd.Parameters.AddWithValue("@name", username);


            using var reader = await cmd.ExecuteReaderAsync();

            while (await reader.ReadAsync())
            {

                var subscribers = new SortedDictionary<string, DateOnly>();
                string subs = reader.GetString("subscribers");
                string[] subsSeparated = subs.Split(',');
                foreach (string sub in subsSeparated)
                {
                   var subProc = sub.Trim().Split(':');
                    string name = subProc[0];
                    var date = DateOnly.Parse(subProc[1]);
                    subscribers.Add(name, date);
                }

                channels.Add(new Channel
                {
                    Id = reader.GetInt32("id"),
                    OwnerID = reader.GetInt32("ownerId"),
                    Name = reader.GetString("name"),
                    Description = reader.GetString("description"),
                    Subscribers = subscribers
                   
                    
                });
            }

            return channels;
        }


    
            public async Task<List<Channel>> GetChannelsUserSubscribedTo(string username)
        {
            var channels = new List<Channel>();
            using var conn = new MySqlConnection(connectionString);

            await conn.OpenAsync();

            string query = @"select * from channels";
            using var cmd = new MySqlCommand(query, conn);


            using var reader = await cmd.ExecuteReaderAsync();

            while (await reader.ReadAsync())
            {
                var subscribers = new SortedDictionary<string, DateOnly>();
                bool isHere = false;
                string subs = reader.GetString("subscribers");
                string[] subsSeparated = subs.Split(',');
                foreach (string sub in subsSeparated)
                {
                    var subProc = sub.Trim().Split(':');
                    string name = subProc[0];
                    if (name == username)
                        isHere = true;
                    var date = DateOnly.Parse(subProc[1]);
                    subscribers.Add(name, date);
                }
                if (isHere)
                {
                    channels.Add(new Channel
                    {
                        Id = reader.GetInt32("id"),
                        OwnerID = reader.GetInt32("ownerId"),
                        Name = reader.GetString("name"),
                        Description = reader.GetString("description"),
                        Subscribers = subscribers


                    });
                }
            }

            return channels;
        }

        public async Task<bool> SubscribeToChannel(string username, string channelName)
        {
            var subscribers = new SortedDictionary<string, DateOnly>();
            using var conn = new MySqlConnection(connectionString);

            await conn.OpenAsync();

            string query = @"select * from channels where name = @channelName";
            using var cmd = new MySqlCommand(query, conn);
            cmd.Parameters.AddWithValue("@channelName", channelName);
            using var reader = await cmd.ExecuteReaderAsync();
            bool isHere = false;
            while (await reader.ReadAsync())
            {
                
                string subs = reader.GetString("subscribers");
                string[] subsSeparated = subs.Split(',');
                foreach (string sub in subsSeparated)
                {
                    var subProc = sub.Trim().Split(':');
                    string name = subProc[0];
                    var date = DateOnly.Parse(subProc[1]);
                   
                    if (name == username)
                    {
                        isHere = true;
                        date = DateOnly.FromDateTime(DateTime.Now);
                    }
                    subscribers.Add(name, date);
                }
 
            }
            await reader.DisposeAsync();

            if (!isHere)
                subscribers.Add(username, DateOnly.FromDateTime(DateTime.Now));
                

                
            string result = string.Join(", ", subscribers.Select(kv => $"{kv.Key}:{kv.Value}"));
            var query2 = "update channels set subscribers = @subscribers where name = @channelName";
            using var cmd2 = new MySqlCommand(query2, conn);
            cmd2.Parameters.AddWithValue("@subscribers", result);
            cmd2.Parameters.AddWithValue("@channelName", channelName);
            return await cmd2.ExecuteNonQueryAsync() > 0;
            

        }


    }
}

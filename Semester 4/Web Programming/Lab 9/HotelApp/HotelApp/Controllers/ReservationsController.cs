using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using System.Security.Claims;
using HotelApp.Services;
using HotelApp.Models;
using System.Diagnostics;

[ApiController]
[Route("api/[controller]")]
[Authorize] 
public class ReservationsController : ControllerBase
{
    private readonly Service service;
    private readonly IHttpContextAccessor _httpContextAccessor;

    public ReservationsController(Service service, IHttpContextAccessor httpContextAccessor)
    {
        this.service = service;
        _httpContextAccessor = httpContextAccessor;
    }

    private int GetCurrentUserId()
    {
        var userIdClaim = _httpContextAccessor.HttpContext?.User?.FindFirst(ClaimTypes.NameIdentifier);
        return userIdClaim != null ? int.Parse(userIdClaim.Value) : 0;
    }

    [HttpGet]
    public async Task<IActionResult> GetAllReservationsForCurrentUser()
    {
        int userId = GetCurrentUserId();
        var reservations = await service.GetUserReservationsAsync(userId);
        return Ok(reservations);
    }

    [HttpGet("{id}")]
    public async Task<IActionResult> GetReservationById(int id)
    {
        int userId = GetCurrentUserId();
        var reservation =  await service.GetReservationByIdAsync(id);

        if (reservation == null || reservation.UserID != userId)
            return NotFound();

        return Ok(reservation);
    }

    [HttpPost]
    public async Task<IActionResult> InsertReservation([FromBody] ReservationRequest reservation)
    {
        int userId = GetCurrentUserId();
        var validated = await service.CheckAvailabilityAsync(reservation.RoomId, reservation.StartDate, reservation.EndDate, -1);
        
        if (validated)
        {
            Debug.WriteLine($"Checking room {reservation.RoomId} from {reservation.StartDate:yyyy-MM-dd} to {reservation.EndDate:yyyy-MM-dd}, excluding ID {-1}");
            var success = await service.InsertReservationAsync(reservation.RoomId, reservation.StartDate, reservation.EndDate, userId);
            return success ? Ok() : BadRequest("Error inserting the reservation!");
        }
        return BadRequest("Room is not available for the selected period");
    }

    [HttpPut("{id}")]
    public async Task<IActionResult> EditReservation(int id, [FromBody] ReservationRequest reservation)
    {
        int userId = GetCurrentUserId();
        var existing =  await service.GetReservationByIdAsync(id);

        if (existing == null || existing.UserID != userId)
            return NotFound();
        var validated = await service.CheckAvailabilityAsync(reservation.RoomId, reservation.StartDate, reservation.EndDate, id);
        if (validated)
        {
            var success = await service.UpdateReservationAsync(id, reservation.StartDate, reservation.EndDate);
            return success ? Ok() : BadRequest("Could not update reservation");
        }
        return BadRequest("Room is not available for the selected period");

           
    }

    [HttpDelete("{id}")]
    public async Task<IActionResult> DeleteReservation(int id)
    {
        int userId = GetCurrentUserId();
        var existing = await service.GetReservationByIdAsync(id);

        if (existing == null || existing.UserID != userId)
            return NotFound();

        var success = await service.DeleteReservationAsync(id);
        return success ? Ok() : BadRequest("Could not delete reservation");
    }

    [HttpDelete("delete-all-reservations")]
    public async Task<IActionResult> DeleteReservationsByUser()
    {
        int userId = GetCurrentUserId();

        var success = await service.DeleteAllReservationsByUser(userId);
        return success ? Ok() : BadRequest("Could not delete reservation");
    }
}


public class ReservationRequest
{
    public int RoomId { get; set; }
    public DateTime StartDate { get; set; }
    public DateTime EndDate { get; set; }
}

using System;
using FlightsAppGoodOne.Data;
using FlightsAppGoodOne.Models.Entities;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace FlightsAppGoodOne.Controllers
{
    [ApiController]
    [Route("api/[controller]")]
    public class AppController : Controller
    {

        private readonly AppDbContext context;
        private readonly IHttpContextAccessor _httpContextAccessor;

        public AppController(AppDbContext context, IHttpContextAccessor httpContextAccessor)
        {
            this.context = context;
            this._httpContextAccessor = httpContextAccessor;
        }

 


        [HttpGet("getFlights")]
        public async Task<IActionResult> GetFlights(string city, string date)
        {
            var flights = await context.Flights.Where(f => f.DestinationCity == city && f.Date == date && f.AvailableSeats > 0).ToListAsync();
            return Ok(flights);
        }

        [HttpGet("getHotels")]
        public async Task<IActionResult> GetHotels(string city, string date)
        {
            var hotels = await context.Hotels.Where(f => f.City == city && f.Date == date && f.AvailableRooms > 0).ToListAsync();
            return Ok(hotels);
        }

        [HttpGet("getReservations")]
        public async Task<IActionResult> GetReservations(string city, string date, string name)
        {
            var reservations = await context.Reservations.Where(r => r.Person == name).ToListAsync();
            return Ok(reservations);
        }

        [HttpPost("ReserveFlight")]
        public async Task<IActionResult> ReserveFlight([FromBody] ReservationRequest request)
        {

            var flight = await context.Flights.FirstOrDefaultAsync(f => f.Id == request.Id);
            if (flight != null)
            {
                flight.AvailableSeats -= 1;
                Reservation res = new Reservation
                {
                    Person = request.Name,
                    Type = "Flight",
                    IdReservedResource = request.Id
                };
                await context.Reservations.AddAsync(res);
                await context.SaveChangesAsync();
                return Ok(res);
            }
            return BadRequest(404);
        }

        [HttpPost("ReserveHotel")]
        public async Task<IActionResult> ReserveHotel([FromBody] ReservationRequest request)
        {
            var flight = await context.Hotels.FirstOrDefaultAsync(f => f.Id == request.Id);
            if (flight != null)
            {
                flight.AvailableRooms -= 1;
                Reservation res = new Reservation
                {
                    Person = request.Name,
                    Type = "Hotel",
                    IdReservedResource = request.Id
                };
                await context.Reservations.AddAsync(res);
                await context.SaveChangesAsync();
                return Ok(res);
            }
            return BadRequest(404);
        }

        [HttpPost("DeleteAllRes")]
        public async Task<IActionResult> DeleteAllRes([FromBody] List<int> reservationIds)
        {
            var reservations = await context.Reservations.Where(r => reservationIds.Contains(r.Id)).ToListAsync();
            if (reservations.Count > 0)
            {
                context.Reservations.RemoveRange(reservations);

                await context.SaveChangesAsync();
                return Ok("Deleted");
            }
            return Ok("Nothing to delete");

        }


        public class ReservationRequest
        {
            public int Id { get; set; }
            public string Name { get; set; }
        }
    }
}

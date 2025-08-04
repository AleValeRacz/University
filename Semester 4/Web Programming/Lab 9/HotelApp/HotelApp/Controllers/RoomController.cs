using Microsoft.AspNetCore.Mvc;
using HotelApp.Services;
using HotelApp.Models;
using Microsoft.AspNetCore.Authorization;


namespace HotelApp.Controllers
{
    [ApiController]
    [Route("api/[controller]")]
    [Authorize]
    public class RoomsController : Controller
    {
        private readonly Service service;

        public RoomsController(Service serv)
        {
            service = serv;
        }

        [HttpGet]
        public async Task<IActionResult> GetAllRooms(int page = 1, int itemsPerPage = 10)
        {
            var result = await service.GetRoomsAsync(page, itemsPerPage);
            return Ok(result);
        }

        [HttpGet("by-type/{type}")]
        public async Task<IActionResult> GetRoomsByType(string type, int page = 1, int itemsPerPage = 6)
        {
            var result = await service.GetRoomsByFilterAsync("Type", type, page, itemsPerPage);
            return Ok(result);
        }

        [HttpGet("by-price/{price}")]
        public async Task<IActionResult> GetRoomsByPrice(decimal price, int page = 1, int itemsPerPage = 6)
        {
            var result = await service.GetRoomsByFilterAsync("Price", price, page, itemsPerPage);
            return Ok(result);
        }

        [HttpGet("by-hotel/{hotel}")]
        public async Task<IActionResult> GetRoomsByHotel(string hotel, int page = 1, int itemsPerPage = 6)
        {
            var result = await service.GetRoomsByFilterAsync("Hotel", hotel, page, itemsPerPage);
            return Ok(result);
        }
    }
}

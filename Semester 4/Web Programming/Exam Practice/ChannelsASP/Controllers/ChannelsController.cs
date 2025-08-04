using Microsoft.AspNetCore.Mvc;
using ChannelsEx.Services;
using Microsoft.AspNetCore.Authentication;
using System.Security.Claims;
using ChannelsEx.Models;
namespace ChannelsEx.Controllers
{
    [ApiController]
    [Route("api/[controller]")]
    public class ChannelsController : Controller
    {
        private readonly Service service;
        private readonly IHttpContextAccessor _httpContextAccessor;
       
        public ChannelsController(Service service, IHttpContextAccessor httpContextAccessor)
        {
            this.service = service;
            this._httpContextAccessor = httpContextAccessor;
        }

        [HttpPost("login")]
        public async Task<ActionResult<Person>> Login([FromBody] string username)
        {
            var user = await service.LogIn(username);

            if (user == null)
                return Unauthorized(new { message = "Username not found" });
            Response.Cookies.Append("username", username, new CookieOptions
            {
                HttpOnly = true,
                SameSite = SameSiteMode.None,
                Secure = true,
                Expires = DateTimeOffset.UtcNow.AddDays(7) 
            });

            
            return Ok(new { message = "Login successful", user });
        }

        [HttpGet("GetChannelsByUser/{username}")]
        public async Task<IActionResult>  GetChannelsByUser(string username)
        {
            var channels = await service.GetChannelsByUser(username);
            return Ok(channels);
        }

        [HttpGet("GetChannelsUserSubscribedTo")]
        public async Task<IActionResult> GetChannelsUserSubscribedTo()
        {
            var username = Request.Cookies["username"];
                var channels = await service.GetChannelsUserSubscribedTo(username);
            return Ok(channels);
        }

        [HttpPut("{channelName}")]
        public async Task<IActionResult> SubscribeToChannel(string channelName)
        {
            var username = Request.Cookies["username"];
            var result = await service.SubscribeToChannel(username, channelName);
            return Ok(result);
        }


    }
}

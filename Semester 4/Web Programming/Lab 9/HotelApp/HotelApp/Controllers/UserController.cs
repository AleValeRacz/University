using System.Security.Claims;
using HotelApp.Models;
using HotelApp.Services;
using Microsoft.AspNetCore.Authentication.Cookies;
using Microsoft.AspNetCore.Authentication;
using Microsoft.AspNetCore.Mvc;

namespace HotelApp.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class UserController: ControllerBase
    {
        private readonly Service service;
        private const string AuthScheme = "MyCookieAuth";

        public UserController(Service serv)
        {
            service = serv;
        }

        [HttpPost("login")]
        public async Task<ActionResult<User>> Login([FromBody] User login)
        {
            var user = await service.LogIn(login.Username, login.Password);

            if (user == null)
                return Unauthorized(new { message = "Username or password is incorrect" });

            var claims = new List<Claim>
            {
                new Claim(ClaimTypes.NameIdentifier, user.Id.ToString()),
                new Claim(ClaimTypes.Name, user.Username)
            };

            var claimsIdentity = new ClaimsIdentity(claims, AuthScheme);

            var authProperties = new AuthenticationProperties
            {
                IsPersistent = true,
                ExpiresUtc = DateTimeOffset.UtcNow.AddHours(1)
            };

            await HttpContext.SignInAsync(AuthScheme,
                new ClaimsPrincipal(claimsIdentity),
                authProperties);

            return Ok(new { message = "Login successful", user });
        }



        [HttpPost("logout")]
        public async Task<IActionResult> Logout()
        {
            await HttpContext.SignOutAsync(AuthScheme);
            return Ok(new { message = "Logged out successfully" });
        }


        [HttpGet("check-session")]
        public IActionResult CheckSession()
        {
            if (User.Identity != null && User.Identity.IsAuthenticated)
            {
                return Ok(new
                {
                    isAuthenticated = true,
                    username = User.Identity.Name
                });
            }

            return Unauthorized(new { isAuthenticated = false });
        }
    }
}

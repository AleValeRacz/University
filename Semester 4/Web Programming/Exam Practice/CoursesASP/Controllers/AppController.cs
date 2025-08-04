using Microsoft.AspNetCore.Mvc;
using CoursesApp.Data;
using Microsoft.EntityFrameworkCore;
using Microsoft.IdentityModel.Tokens;
using Microsoft.AspNetCore.Http.HttpResults;
using Microsoft.AspNetCore.Mvc.ViewFeatures;
namespace CoursesApp.Controllers
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


        [HttpPost("login")]
        public async Task<IActionResult> login([FromBody] string name)
        {
            var prof = await context.Persons.Where(p => p.Name == name).FirstOrDefaultAsync();
            if (prof == null || !prof.Role.Equals("professor"))
            {
                return BadRequest(404);
            }
            return Ok(prof);
        }

        [HttpGet("GetAllParticipantsForACourse")]
        public async Task<IActionResult> GetParticipants(string name)
        {
            var course = await context.Courses.Where(c => c.CourseName == name).FirstOrDefaultAsync();
            if (course == null)
            {
                return BadRequest(404);
            }
            if(!course.Participants.IsNullOrEmpty())
            {
                var participants = course.Participants.Trim().Split(',').ToList();
                return Ok(participants);
            }
            return Ok();
            
        }

        [HttpGet("GetAllCoursesPerPerson")]
        public async Task<IActionResult> GetCourses(string name)
        {
            List<string> cors= new List<string>();
            var courses = await context.Courses.ToListAsync();
            if (courses == null)
            {
                return BadRequest(404);
            }
            foreach(var course in courses)
            {
                if (!course.Participants.IsNullOrEmpty())
                {
                    var participants = course.Participants.Trim().Split(',').ToList();
                    foreach(var participant in participants)
                    {
                        if (participant.Equals(name))
                            cors.Add(course.CourseName);
                    }
                    
                }

            }
            return Ok(cors);

        }

        [HttpGet("AssignGrade")]
        public async Task<IActionResult> AssignGrade( string studentName, string courseName, int grade)
        {
            var course = await context.Courses.Where(c => c.CourseName == courseName).FirstOrDefaultAsync();
            if (course == null)
                return BadRequest(404);

            var participants = course.Participants?.Trim().Split(',').Where(s => !string.IsNullOrEmpty(s)).ToList() ?? new List<string>();
            var gradesList = course.Grades?.Trim().Split(',').Where(s => !string.IsNullOrEmpty(s)).ToList() ?? new List<string>();

            if (!participants.Contains(studentName))
            {
                participants.Add(studentName);
            }

            bool foundGrade = false;
            var newGrades = new List<string>();

            foreach (var item in gradesList)
            {
                var parts = item.Split(':');
                if (parts.Length == 2 && parts[0] == studentName)
                {
                    newGrades.Add(studentName + ":" + grade.ToString());
                    foundGrade = true;
                }
                else
                {
                    newGrades.Add(item);
                }
            }

            if (!foundGrade)
            {
                newGrades.Add(studentName + ":" + grade.ToString());
            }

            course.Participants = string.Join(",", participants);
            course.Grades = string.Join(",", newGrades);

            await context.SaveChangesAsync();
            return Ok();
        }


    }


}

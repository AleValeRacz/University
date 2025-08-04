using CoursesApp.Models;
using Microsoft.EntityFrameworkCore;
namespace CoursesApp.Data
{

    public class AppDbContext: DbContext
    {
        public AppDbContext(DbContextOptions<AppDbContext> options): base(options)
        {

        }

        public DbSet<Course> Courses { get; set; }
        public DbSet<Person> Persons { get; set; }


    }
}

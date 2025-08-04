using System.ComponentModel.DataAnnotations;
namespace CoursesApp.Models
{
    public class Course
    {
        [Key]
        public int Id { get; set; }
        public int ProfessorId { get; set; }

        public string CourseName { get; set; }
        public string Participants { get; set; }
        public string Grades { get; set; }
    }
}

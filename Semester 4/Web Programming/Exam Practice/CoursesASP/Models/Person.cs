using System.ComponentModel.DataAnnotations;
namespace CoursesApp.Models
{
    public class Person
    {

        [Key]
        public int Id { get; set; }
        public string Name { get; set; }
        public string Role { get; set; }

        
    }
}

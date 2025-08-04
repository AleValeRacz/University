using System.ComponentModel.DataAnnotations;

namespace FlightsAppGoodOne.Models.Entities
{
    public class Hotel
    {
        [Key]
        public int Id { get; set; }
        public string Name { get; set; }
        public string Date { get; set; }
        public string City { get; set; }
        public int AvailableRooms { get; set; }
    }
}

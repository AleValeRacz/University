using System.ComponentModel.DataAnnotations;

namespace FlightsAppGoodOne.Models.Entities
{
    public class Flight
    {
        [Key]
        public int Id { get; set; }
        public string Date { get; set; }
        public string DestinationCity { get; set; }
        public int AvailableSeats { get; set; }
    }
}

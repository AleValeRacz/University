using System.ComponentModel.DataAnnotations;

namespace FlightsAppGoodOne.Models.Entities
{
    public class Reservation
    {
        [Key]
        public int Id { get; set; }
        public string Person {  get; set; }

        public string Type { get; set; }

        public int IdReservedResource {  get; set; }
    }
}

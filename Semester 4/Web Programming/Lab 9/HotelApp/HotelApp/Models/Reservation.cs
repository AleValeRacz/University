namespace HotelApp.Models
{
    public class Reservation
    {
        public int Id { get; set; }
        public DateTime StartDate { get; set; }
        public DateTime EndDate { get; set; }
        public int RoomNumber { get; set; }
        public string Hotel { get; set; }
        public int UserID { get; set; }
    }
}

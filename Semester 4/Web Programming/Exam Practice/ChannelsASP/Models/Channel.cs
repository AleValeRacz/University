namespace ChannelsEx.Models
{
    public class Channel
    {
        public int Id { get; set; }
        public int OwnerID { get; set; }
        public string Name { get; set; }
       public string Description { get; set; }
        public SortedDictionary<string, DateOnly> Subscribers { get; set; }

    }
}

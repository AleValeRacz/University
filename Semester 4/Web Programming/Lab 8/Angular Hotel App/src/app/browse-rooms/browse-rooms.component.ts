import { Component,OnInit } from '@angular/core';
import { RoomService } from '../room.service';
import { Router } from '@angular/router'; 
@Component({
  selector: 'app-browse-rooms',
  templateUrl: './browse-rooms.component.html',
  styleUrl: '../style.css',
})
export class BrowseRoomsComponent implements OnInit {
  rooms: any[] = [];
  currentPage = 0; 
  pageSize = 4;
  totalPages = 0;

  categoryFilter = '';
  priceFilter = '';
  hotelFilter = '';

  constructor(private service: RoomService, private router: Router) {}

  ngOnInit(): void {
    console.log('ngOnInit called');
    this.loadRooms();
    this.loadRooms();
  }
  loadRooms(): void {
    this.service.getAllRooms(this.currentPage, this.pageSize).subscribe((data: any) => {
      console.log('Rooms loaded:', data);
      this.rooms = data.rooms;
      this.totalPages = data.totalPages;
    });
  }

  

  goToPreviousPage(): void {
    if (this.currentPage > 0) {
      this.currentPage--;
      this.loadRooms();
      this.loadRooms();
    }
  }

  goToNextPage(): void {
    if (this.currentPage < this.totalPages - 1) {
      this.currentPage++;
      this.loadRooms();
      this.loadRooms();
    }
  }
  filterByTypeWrapper(type: string): void{
    this.filterByType(type);
    this.filterByType(type);
  }

    filterByPriceWrapper(price: string): void{
    this.filterByPrice(price);
    this.filterByPrice(price);
  }
    filterByHotelWrapper(hotel: string): void{
    this.filterByHotel(hotel);
    this.filterByHotel(hotel);
  }
  
  filterByType(type: string): void {
    this.service.getRoomsByType(type, this.currentPage, this.pageSize).subscribe((data: any) => {
      this.rooms = data.rooms ?? data;
      this.currentPage = 0;
      this.totalPages = data.totalPages ?? 1;
      setTimeout(() => {
        console.log('Filtered rooms by price:', this.rooms);
      });
    });
  }

  filterByPrice(price: string): void {
    this.service.getRoomsByPrice(price, this.currentPage, this.pageSize).subscribe((data: any) => {
      this.rooms = data.rooms ?? data;
      this.currentPage = 0;
      this.totalPages = data.totalPages ?? 1;
    });
  }

  filterByHotel(hotel: string): void {
    this.service.getRoomsByHotel(hotel, this.currentPage, this.pageSize).subscribe((data: any) => {
      this.rooms = data.rooms ?? data;
      this.currentPage = 0;
      this.totalPages = data.totalPages ?? 1;
    });
  }

  addReservation(roomId: number): void {
    this.router.navigate(['/add-reservation'], { queryParams: { id: roomId } });
  }

  goToMainPage(): void {
    this.router.navigate(['/home-page']);
  }
}


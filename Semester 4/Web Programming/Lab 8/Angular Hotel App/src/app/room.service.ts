// src/app/room.service.ts
import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';
import { Router } from '@angular/router';

@Injectable({
  providedIn: 'root',
})
export class RoomService {
  private baseUrl = 'http://localhost:80/HotelApp/DBUtils.php';

  constructor(private http: HttpClient, private router: Router) {}

  getAllRooms(currentPage: number, itemsPerPage: number): Observable<any> {
    return this.http.get(`${this.baseUrl}?action=getAllRooms&page=${currentPage+1}&itemsPerPage=${itemsPerPage}`);
  }

  getRoomsByType(type: string, currentPage: number, itemsPerPage: number): Observable<any> {
    return this.http.get(`${this.baseUrl}?action=getRoomsByType&page=${currentPage+1}&itemsPerPage=${itemsPerPage}&Type=${type}`);
  }

  getRoomsByPrice(price: string, currentPage: number, itemsPerPage: number): Observable<any> {
    return this.http.get(`${this.baseUrl}?action=getRoomsByPrice&page=${currentPage+1}&itemsPerPage=${itemsPerPage}&Price=${price}`);
    }

  getRoomsByHotel(hotel: string,currentPage: number, itemsPerPage: number ): Observable<any> {
        return this.http.get(`${this.baseUrl}?action=getRoomsByHotel&page=${currentPage+1}&itemsPerPage=${itemsPerPage}&Hotel=${hotel}`);
  }

  goToMainPage(): void {
    this.router.navigate(['/home-page']);
  }

  
}
import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';
import { Router } from '@angular/router';

@Injectable({
  providedIn: 'root',
})
export class ReservationService {
  private baseUrl = 'http://localhost:80/HotelApp/DBUtils.php';

  constructor(private http: HttpClient, private router: Router) {}

  getAllReservations(): Observable<any> {
    return this.http.get(`${this.baseUrl}?action=getAllReservations`);
  }

    getReservationById(id: number): Observable<any> {
    return this.http.get(`${this.baseUrl}?action=getReservationById&ID=${id}`);
  }

    editReservation(id: number, startDate: Date, endDate: Date): Observable<any> {
        return this.http.get(`${this.baseUrl}?action=editReservation&id=${id}&start_date=${startDate}&end_date=${endDate}`);
    }

    insertReservation(
        startDate: Date,
        endDate: Date,
        roomId: number,
    ): Observable<any> {
        return this.http.get(`${this.baseUrl}?action=insertReservation&room_id=${roomId}&start_date=${startDate}&end_date=${endDate}`);
    }

    deleteReservation(id: number): Observable<any> {
        return this.http.get(`${this.baseUrl}?action=deleteReservation&id=${id}`);
    }

    checkAvailability(room_id: number, startDate: Date, endDate: Date, id: number): Observable<any> {
        return this.http.get(`${this.baseUrl}?action=checkAvailability&room_id=${room_id}&start_date=${startDate}&end_date=${endDate}&id=${id}`);
    }






}
import { Component, OnInit } from '@angular/core';
import { ActivatedRoute, Router } from '@angular/router';
import { ReservationService } from '../reservation.service';
@Component({
  selector: 'app-edit-reservation',
  templateUrl: './edit-reservation.component.html',
  styleUrl: '../style.css',
})
export class EditReservationComponent implements OnInit {
    startDate: Date = new Date();
    endDate: Date = new Date();
    reservationId: number;
    roomId: number = 0;
  
    constructor(
      private reservationService: ReservationService,
      private route: ActivatedRoute,
      private router: Router,
  
    ) {
      this.reservationId = Number(this.route.snapshot.queryParamMap.get('id'));
    }
  
    ngOnInit() : void {
    this.reservationService.getReservationById(this.reservationId).subscribe({
      next: (reservation) => {
        this.startDate = new Date(reservation.StartDate);
        this.endDate = new Date(reservation.EndDate);
        this.roomId = reservation.RoomID;
      },
      error: () => {
        alert('Error loading reservation details');
        this.router.navigate(['/browse-reservations']);
      }
    });
  
    }
  
    editReservation(): void {
    let today = new Date();
    today.setHours(0, 0, 0, 0); 
  
    const start = new Date(this.startDate);
    const end = new Date(this.endDate);
    if (start< end) {
      if (start < today) {
        alert('You cannot create a reservation in the past!');
        return;
      }
  
      this.reservationService
        .checkAvailability(this.roomId, this.startDate, this.endDate, this.reservationId)
        .subscribe({
          next: (isAvailable) => {
            if (isAvailable === true || isAvailable === 'true') {
              this.reservationService
                .editReservation(this.reservationId, this.startDate, this.endDate)
                .subscribe({
                  next: (res) => {
                    if (res === 0) {
                      alert('Reservation could not be edited!');
                    } else {
                      this.startDate = new Date();
                      this.endDate = new Date();
                      alert('Reservation added successfully!');
                    }
                  },
                  error: () => alert('Error adding reservation'),
                });
            } else {
              alert('Room is not available for the selected dates!');
            }
          },
          error: () => alert('Error checking availability'),
        });
    } else {
      alert('End date must be after start date!');
    }
  }
  
  
    viewAllReservations(): void {
      this.router.navigate(['/browse-reservations']);
    }
  
    returnToHomePage(): void {
      this.router.navigate(['/home-page']);
    }
  }



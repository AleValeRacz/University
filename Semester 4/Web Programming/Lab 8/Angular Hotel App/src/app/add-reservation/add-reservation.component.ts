import { Component } from '@angular/core';
import { ActivatedRoute, Router } from '@angular/router';
import { ReservationService } from '../reservation.service';
@Component({
  selector: 'app-add-reservation',
  templateUrl: './add-reservation.component.html',
  styleUrl: '../style.css',
})
export class AddReservationComponent {
  startDate: Date = new Date();
  endDate: Date = new Date();
  roomId: number;

  constructor(
    private reservationService: ReservationService,
    private route: ActivatedRoute,
    private router: Router,

  ) {
    this.roomId = Number(this.route.snapshot.queryParamMap.get('id'));
  }

  ngOnInit() {

  }

  addReservation(): void {
  let today = new Date();
  today.setHours(0, 0, 0, 0); 
  const start = new Date(this.startDate);
  const end = new Date(this.endDate);
  if (start < end) {
    if (start < today) {
      alert('You cannot create a reservation in the past!');
      return;
    }

    this.reservationService
      .checkAvailability(this.roomId, this.startDate, this.endDate, -1)
      .subscribe({
        next: (isAvailable) => {
          if (isAvailable === true || isAvailable === 'true') {
            this.reservationService
              .insertReservation(this.startDate,this.endDate, this.roomId)
              .subscribe({
                next: (res) => {
                  if (res === 0) {
                    alert('Reservation could not be added!');
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

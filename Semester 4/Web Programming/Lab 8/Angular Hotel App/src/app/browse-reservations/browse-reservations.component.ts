import { Component, OnInit } from '@angular/core';
import { ReservationService } from '../reservation.service';
import { Router } from '@angular/router';

@Component({
  selector: 'app-browse-reservations',
  templateUrl: './browse-reservations.component.html',
  styleUrl: '../style.css',
})
export class BrowseReservationsComponent implements OnInit{

   reservations: any[] = [];
   reservationss: any;

   constructor(
    private reservationService: ReservationService, private router: Router, 
  ) {}


    ngOnInit(): void {
   this.loadReservations();
    this.loadReservations();
    // setTimeout(() => {
    //   this.reservations = [{
    //     "ID": 1,
    //     "StartDate": "2023-10-01",
    //     "EndDate": "2023-10-05",
    //     "RoomID": 101,
    //     "UserID": 1
    //   },
    //   {
    //     "ID": 2,
    //     "StartDate": "2023-10-10",
    //     "EndDate": "2023-10-15",
    //     "RoomID": 102,
    //     "UserID": 2
    //   },
    //   {
    //     "ID": 3,
    //     "StartDate": "2023-10-20",
    //     "EndDate": "2023-10-25",
    //     "RoomID": 103,
    //     "UserID": 3
    //   }];
    // }, 5000);
  }

  loadReservations(): void {
    this.reservationService.getAllReservations().subscribe(data=> {
      this.reservationss = [...data];
      console.log(this.reservationss, data?.length);
    }
    );
  }
  deleteReservation(id: number): void {
  if (confirm('Are you sure you want to delete this reservation?')) {
    this.reservationService.deleteReservation(id).subscribe(
      () => {
        alert('Reservation deleted successfully!');
        this.loadReservations();
        window.location.reload();
      },
      (error) => {
        alert('Could not delete the reservation!');
      }
    );
  }
}

  editReservation(id: number): void {
    this.router.navigate(['/edit-reservation'],  {queryParams: {id: id}}).then(_ => {
    });
  }

  returnToHomePage(): void {
    this.router.navigate(['/home-page']);
  }

}

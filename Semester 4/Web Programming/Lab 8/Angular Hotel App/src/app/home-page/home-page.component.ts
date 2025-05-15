import { Component } from '@angular/core';
import { Router } from '@angular/router';
@Component({
  selector: 'app-home-page',
  templateUrl: './home-page.component.html',
  styleUrl: '../style.css',
})
export class HomePageComponent {
constructor(private router: Router){}
  goToBrowseRooms(): void {
    this.router.navigate(['/browse-rooms']);
  }
  goToReservations(): void {
    this.router.navigate(['/browse-reservations']);
  }
}

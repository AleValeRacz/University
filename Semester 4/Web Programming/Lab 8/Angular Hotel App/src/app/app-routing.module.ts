import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';

import {BrowseRoomsComponent} from './browse-rooms/browse-rooms.component';
import { HomePageComponent } from './home-page/home-page.component';
import { BrowseReservationsComponent } from './browse-reservations/browse-reservations.component';
import { AddReservationComponent } from './add-reservation/add-reservation.component';
import { EditReservationComponent } from './edit-reservation/edit-reservation.component';


const routes: Routes = [
{path: '', redirectTo: '/home-page', pathMatch: 'full'},
{path: 'home-page', component: HomePageComponent},
  {path: 'browse-rooms', component: BrowseRoomsComponent},
  {path: 'browse-reservations', component: BrowseReservationsComponent},
  {path: 'add-reservation', component: AddReservationComponent},
  {path : 'edit-reservation', component: EditReservationComponent},
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule {
}
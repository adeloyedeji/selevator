# Content
- [Introduction](#introduction)
- [Project goals](#project-goals)
- [Requirements](#requirement)
- [Considerations](#considerations)

## Introduction
An iterative attempt to design an elevator system. This project *should* be updated from time to time.

## Project goals
Design an effective, efficient elevator system.

## Requirement
A building has 2 elevators and 15 floors. This software should be able to efficiently move people up and down the building without much delays.

### Considerations
- At the beginning of the day, both elevators are at ground floor. Also, when there are no requests to service, an elevator *should* return to the ground floor.
- An elevator can be disabled at any time: 
    - Use case for this scenario is when you have a high profile guest that needs to be transported between floors, for security reasons, other elevators can be disabled while the guest is in transit and enabled once they've reached their destination.
    - An elevator could also be under repair and cannot service any request.
- An elevator can be requested from any floor.
- An elevator request can only be cancelled if no elevator has been dispatched to that floor; once an elevator has been dispatched and a cancel is requested, the dispatcher should automatically re-route the elevator to the next request.
- An elevator can only move in one direction:
    - If an elevator is requested from 3rd floor to the 7th floor and another request is made from the 4th floor to the ground floor, if an elevator was dispatched to service the first request, it can only service requests in that direction i.e. requests to go up.
    - If an elevator is requested from 3rd floor to the 7th floor and another request is made from 2nd floor to the 8th floor, elevator default action should be to service all requests in it's direction which in this case will be to go to 2nd floor and service that request as well as the first request from 3rd floor. This should be made configurable at runtime to behave otherwise i.e. fulfill the first request and the second request next.
- Elevator **MUST** have maximum load weight it can support:
    - If the total load on the elevator exceeds the maximum weight supported, an error should be displayed.
- An elevator **MUST** have maximum time it can remain on a floor that is not the default floor i.e. ground floor. 
    - When an elevator is requested, it moves to the point of requests and the doors open. The doors should not stay open more than the configured maximum time the elevator can remain open. Once the elevator doors are open, requestors can keep the doors open for the configured time. After the configured time has been elapsed, the elevator **MUST** issue a closing count down (starting from a configured upper range to 0) to indicate it will forcefully close the doors.
    - When an elevator is requested and gets to the point of requests, the doors open and remain open for a configured amount of time after which the doors **MUST** begin to close. The doors can be held open by the occupants of the elevator so long as the configured maximum open time has not been reached.
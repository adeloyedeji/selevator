# Content

# Design thoughts
- This is a console based application.
- Input is entered 

# Entities
- Elevator
    - Properties:
        - Max Weigth (Kg): Maximum load the elevator can carry.
        - State: The current state of the elevator.
        - Floor: The floor number the elevator is currently been held.
        - Maximum open time (seconds): Maximum amount of time the elevator doors **MUST** remain open before issueing a closing count down.
        - Close count down upper limit: The upper limit to begin the closing count down from.
- Floor
    - Properties:
        - Number: Floor number

# High Level Services
- Timer Service: Manages timing operations; when elevator doors opens, begins a timer, fire an event to begin countdown after timer elapses, etc.
- Dispatch Service: Manages dispatching elevators to service requests.

# Low Level Services
- Thread manager: Manages creating threads for each elevator and associated requests
- Logging manager: Provides robust logging
- Console manager: Manages console inputs/outputs
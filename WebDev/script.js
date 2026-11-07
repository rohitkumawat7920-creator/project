/* ======================================================
   Basic JavaScript for Parking Management System
   Concepts Used:
   - Variables and Arrays
   - Basic Functions and if/else conditions
   - For loops
   - Standard DOM manipulation (document.getElementById)
   ====================================================== */

// Step 1: Configuration variables
var totalSlots = 10;   // Total number of parking spaces available
var parkedCars = [];   // Array to store all parked car objects

// ======================================================
// Helper Function: Show message to the user (Success or Error)
// ======================================================
function showMessage(text, isError) {
    var messageElement = document.getElementById("message");
    messageElement.innerText = text;

    if (isError) {
        messageElement.className = "message msg-error";
    } else {
        messageElement.className = "message msg-success";
    }
}

// ======================================================
// MODULE 1: Update the Counter / Status Dashboard
// ======================================================
function updateStatus() {
    var parkedCount = parkedCars.length;
    var availableSlots = totalSlots - parkedCount;

    // Update numbers on the screen
    document.getElementById("totalSlots").innerText = totalSlots;
    document.getElementById("parkedCount").innerText = parkedCount;
    document.getElementById("availableSlots").innerText = availableSlots;
}

// ======================================================
// MODULE 4: Render the Table of Parked Cars
// ======================================================
function renderTable() {
    var tableBody = document.getElementById("carsTableBody");

    // If no cars are parked, show empty message
    if (parkedCars.length === 0) {
        tableBody.innerHTML = '<tr><td colspan="4" class="empty-text">No cars parked currently.</td></tr>';
        return;
    }

    // Build the table rows using a simple for loop
    var rowsHTML = "";
    for (var i = 0; i < parkedCars.length; i++) {
        var car = parkedCars[i];
        var slotNumber = i + 1; // Slot index starting from 1

        rowsHTML += "<tr>";
        rowsHTML += "<td>Slot " + slotNumber + "</td>";
        rowsHTML += "<td>" + car.carNumber + "</td>";
        rowsHTML += "<td>" + car.ownerName + "</td>";
        rowsHTML += "<td>" + car.entryTime + "</td>";
        rowsHTML += "</tr>";
    }

    // Insert rows into the table
    tableBody.innerHTML = rowsHTML;
}

// ======================================================
// MODULE 2: Park a Car (Add car to the array)
// ======================================================
function parkCar() {
    // 1. Get values from the input fields
    var carNumberInput = document.getElementById("carNumber");
    var ownerNameInput = document.getElementById("ownerName");

    var carNumber = carNumberInput.value.trim().toUpperCase();
    var ownerName = ownerNameInput.value.trim();

    // 2. Validate input: make sure fields are not empty
    if (carNumber === "" || ownerName === "") {
        showMessage("Please enter both Car Number and Owner Name!", true);
        return;
    }

    // 3. Check if parking lot is full
    if (parkedCars.length >= totalSlots) {
        showMessage("Parking lot is full! No slots available.", true);
        return;
    }

    // 4. Check if this car is already parked
    for (var i = 0; i < parkedCars.length; i++) {
        if (parkedCars[i].carNumber === carNumber) {
            showMessage("Car " + carNumber + " is already parked!", true);
            return;
        }
    }

    // 5. Get current time for entry stamp
    var now = new Date();
    var timeString = now.toLocaleTimeString([], { hour: '2-digit', minute: '2-digit' });

    // 6. Create car object and add to parkedCars array
    var newCar = {
        carNumber: carNumber,
        ownerName: ownerName,
        entryTime: timeString
    };

    parkedCars.push(newCar);

    // 7. Clear the form inputs
    carNumberInput.value = "";
    ownerNameInput.value = "";

    // 8. Update screen displays
    showMessage("Car " + carNumber + " parked successfully!", false);
    updateStatus();
    renderTable();
}

// ======================================================
// MODULE 3: Remove a Car (Remove car from the array)
// ======================================================
function removeCar() {
    // 1. Get value from the remove input field
    var removeInput = document.getElementById("removeCarNumber");
    var carNumberToRemove = removeInput.value.trim().toUpperCase();

    // 2. Validate input
    if (carNumberToRemove === "") {
        showMessage("Please enter a Car Number to remove!", true);
        return;
    }

    // 3. Search for the car in the array using a simple loop
    var foundIndex = -1;
    for (var i = 0; i < parkedCars.length; i++) {
        if (parkedCars[i].carNumber === carNumberToRemove) {
            foundIndex = i;
            break; // Stop loop once found
        }
    }

    // 4. If car was not found
    if (foundIndex === -1) {
        showMessage("Car " + carNumberToRemove + " was not found in the parking lot!", true);
        return;
    }

    // 5. Remove car from the array using splice
    parkedCars.splice(foundIndex, 1);

    // 6. Clear input field
    removeInput.value = "";

    // 7. Update screen displays
    showMessage("Car " + carNumberToRemove + " has been successfully removed!", false);
    updateStatus();
    renderTable();
}

// Initial setup call when page loads
updateStatus();
renderTable();

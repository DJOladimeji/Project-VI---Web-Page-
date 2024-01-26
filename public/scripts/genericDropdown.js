// Toggle the "active" class to control the visibility of the dropdown content
function toggleDropdown() {
    var dropdown = document.querySelector('.dropdown');
    dropdown.classList.toggle('active');
}

// Close the dropdown if the user clicks outside of it
window.onclick = function(event) {
    if (!event.target.matches('.dropdown img')) {
        var dropdowns = document.querySelectorAll('.dropdown');
        dropdowns.forEach(function(dropdown) {
            if (dropdown.classList.contains('active')) {
                dropdown.classList.remove('active');
            }
        }); 
    }
}


function handleDropdownChange(selectedValue) {
    if (selectedValue === "add") {
        window.location.href = "Add_Task_Page.html"; // Replace with the actual file name
    }
}

function confirmAndDeleteTask() {
    // Call confirmDeleteTask first
    confirmDeleteTask();

    // Then call myFunction
    myFunction();
}

function confirmDeleteTask() {
    var confirmDelete = confirm("Do you want to delete this task?");
    if (confirmDelete) {
        // If the user clicks "OK" in the confirmation dialog, proceed with deletion
        deleteTask();
    }
    // If the user clicks "Cancel" or closes the dialog, do nothing
}

function deleteTask() {
    // Implement your deletion logic here
    alert("Task deleted!");
}
function myFunction(){
    var action = "/deleteTask"; 
    var param = document.querySelector('h1').innerText;
    action += param;
    document.getElementById("DeleteTask").action = action; 
    document.getElementById("DeleteTask").submit();
}

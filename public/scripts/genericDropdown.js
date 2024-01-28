// Toggle the "active" class to control the visibility of the dropdown content
function toggleDropdown() {
    var dropdown = document.querySelector('.dropdown');
    dropdown.classList.toggle('active');
}

function toggleDropdown2() {
    var dropdown = document.getElementById("dropdown");
    dropdown.style.display = (dropdown.style.display === "none") ? "block" : "none";
}

function sortBy(option) {
    var route = (option === 'Name') ? '/sortByName' : '/sortByDate';

    // Making an OPTIONS request to the specified route
    var xhr = new XMLHttpRequest();
    xhr.open('GET', route, true);
    xhr.onreadystatechange = function() {
        if (xhr.readyState === 4) {
            if (xhr.status === 200) {
                console.log('OPTIONS request successful');
                // Perform additional actions if needed

                window.location.reload();
            } else {
                console.error('Error making OPTIONS request');
            }
        }
    };
    xhr.send();
}

// Attach the event listener to all elements with the 'dropdown' class
var dropdownElements = document.querySelectorAll('.dropdown');
dropdownElements.forEach(function (element) {
    element.addEventListener('click', toggleDropdown);
});


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
    //var action = "/deleteTask/"; 
    var action = "/deleteTask"; 
    //var param = document.querySelector('h1').innerText;
    //action += param;
    document.getElementById("DeleteTask").action = action; 
    document.getElementById("DeleteTask").submit();

    fetch('/deleteTask', {
        method: 'DELETE', 
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify({ taskName: document.querySelector('h1').innerText }),  
    })
    .then(response => {
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }
        return response.json();
    })
    .then(data => {
        // Handle the response data
        console.log(data);
    })
    .catch(error => {
        // Handle errors
        console.error('Error:', error);
    }); 
}

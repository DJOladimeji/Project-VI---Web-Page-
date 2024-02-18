function validateForm(event) {
    event.preventDefault(); // Prevents the form from submitting in the traditional way

    var username = document.getElementById("username").value;
    var password = document.getElementById("password").value;
    var errorMessage = document.getElementById("errorMessage");

    // Simple validation
    if (username === "" || password === "") {
        errorMessage.textContent = "Username and password are required!";
    } else {
        // Perform further authentication or form submission logic here
        errorMessage.textContent = ""; // Clear any previous error messages
        alert("Sign in successful!");
    } 
}

function signIn() {
    const username = document.getElementById('username').value;
    const password = document.getElementById('password').value;
    const errorMessage = document.getElementById('error-message');
  
    // Add your authentication logic here
    // For simplicity, let's check if the username and password are not empty
    if (username.trim() === '' || password.trim() === '') {
      errorMessage.textContent = 'Username and password are required.';
    } else {
      // Successful sign-in
      errorMessage.textContent = '';
      alert(`Welcome, ${username}!`);
      // You can redirect the user to another page or perform other actions here
    }  
  }
  
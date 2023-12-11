import requests

def send_command(command):
    url = "http://localhost:3001"
    payload = {"command": command}
    response = requests.post(url, data=payload)
    if response.status_code == 200:
        print("Command sent successfully!")
    else:
        print("Failed to send command.")

def main():
    while True:
        user_input = input("Enter a command: ")
        send_command(user_input)

if __name__ == "__main__":
    main()

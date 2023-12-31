import sys
import json
import urllib.request
import datetime

if len(sys.argv) == 2:
    jsonURL = sys.argv[1]
else:
    print("Error: Expecting only 1 command line argument (the exact URL you are trying to access, see README.md)")

try:
    # Open the URL and read its content
    with urllib.request.urlopen(jsonURL) as url:
        data = json.loads(url.read().decode())

        # here we create unique name for file
        today = datetime.datetime.today()
        year = today.year
        month = today.month
        day = today.day
        hour = today.hour
        minute = today.minute
        second = today.second

        # Find the last occurrence of "/"
        lastSlashIndex = jsonURL.rfind("/")

        # Extract the substring after the last "/" and exclude ".json"
        subString = jsonURL[lastSlashIndex + 1:-5] # this allows us to specify which source we are reading from

        # Specify the output text file path
        outputFilePath = ""+str(subString)+"_"+str(year)+"-"+str(month)+"-"+str(day)+"T"+str(hour)+"-"+str(minute)+"-"+str(second)+".txt"

        # Write JSON data to the text file
        with open(outputFilePath, 'w') as text_file:
            text_file.write(json.dumps(data, indent=4))

        print(f"JSON data from {subString} has been written to {outputFilePath}")

except Exception as e:
    print(f"Failed to retrieve data from {jsonURL}. Error: {e}")

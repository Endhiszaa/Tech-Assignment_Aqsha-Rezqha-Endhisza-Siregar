from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/data', methods=['POST'])
def receive_data():
    if request.is_json:
        data = request.get_json()
        temperature = data.get('temperature')
        humidity = data.get('humidity')
        if temperature is not None and humidity is not None:
            print(f"Received temperature: {temperature}")
            print(f"Received humidity: {humidity}")
            response = {
                "status": "success",
                "message": "Data received",
                "data": data
            }
            return jsonify(response), 200
        else:
            response = {
                "status": "error",
                "message": "Invalid data"
            }
            return jsonify(response), 400
    else:
        response = {
            "status": "error",
            "message": "Request must be JSON"
        }
        return jsonify(response), 400

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)

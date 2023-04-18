let control_name = document.getElementById('control_name');
let control_pin = document.getElementById('control_pin');
let control_value = document.getElementById('control_value');

let control_button = document.getElementById('control_button');

let control_list = document.getElementById('control_list');
let monitor_list = document.getElementById('monitoring_list');

let url = "https://643cf2436afd66da6ae7fca7.mockapi.io/api/v1/";

function getControl(){
    fetch(url+"control")
    .then((response) => response.json())
    .then((data) => listControl(data));
}

function getMonitoring(){
    fetch(url+"monitoring")
    .then((response) => response.json())
    .then((data) => listMonitoring(data));
}

function listMonitoring(data){
    console.log(data);

    for (const value of data) {
        const monitoringLI = document.createElement('li');
        let status;
        if(value.monitoring_name == "Suhu") {
            status = '°C'
        } else {
            status = '%'
        }
        monitoringLI.innerHTML = `
        <div class="card">
        <div class="card-body">
            <div class="row">
                <div class="col">
                    <strong>${value.monitoring_name}</strong>
                </div>
                <div class="col">
                    <strong>${value.monitoring_value} ${status}</strong>
                </div>
            </div>
        </div>
        </div>`
        // const controlUL = document.querySelector('#control_list');
        const monitoringUL = monitor_list;
        monitoringUL.append(monitoringLI);
    }
}

function listControl(data){
    console.log(data);

    for (const value of data) {
        const controlLI = document.createElement('li');
        let status;
        if(value.control_value == 1) {
            status = '<button class="btn btn-success" id="control_status">ON</button>'
        } else {
            status = '<button class="btn btn-danger" id="control_status">OFF</button>'
        }
        controlLI.innerHTML = `
        <div class="card">
        <div class="card-body">
            <div class="row">
                <div class="col">
                    <strong>${value.control_name}</strong>
                </div>
                <div class="col">
                    <strong>${value.control_pin}</strong>
                </div>
                <div class="col">
                    <strong>${status}</strong>
                </div>
            </div>
        </div>
        </div>`
        // const controlUL = document.querySelector('#control_list');
        const controlUL = control_list;
        controlUL.append(controlLI);
    }
}
getControl();
getMonitoring();

control_button.addEventListener("click", () =>{
    console.log(control_name.value);
    console.log(control_pin.value);
    console.log(control_value.value);
})

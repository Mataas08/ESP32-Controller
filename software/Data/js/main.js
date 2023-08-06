// Start looking for gamepads
Controller.search();

///support
window.addEventListener('load', function() {
    if (Controller.supported) {
        document.body.setAttribute('data-supported', 'true');
    } else {
        document.body.setAttribute('data-supported', 'false');
    }
}, false);

// Input events
window.addEventListener('gc.button.press', updateButton, false);
window.addEventListener('gc.button.hold', updateButton, false);
window.addEventListener('gc.button.release', updateButton, false);
window.addEventListener('gc.analog.change', updateAnalog, false);

// Controller events
window.addEventListener('gc.controller.found', showControllerTables, true);
window.addEventListener('gc.controller.lost', destroyTable, false);

// Functions
function destroyTable(event) {
    if (Controller.controllerCount === 0) {
        document.getElementById('instructions').className = '';
    }

    var element = document.getElementById('controller_' + event.detail.index);

    element.className = 'controller hidden';
    element.addEventListener('transitionend', function() {
        element.parentElement.removeChild(element);
    }, false);
}

function makeControllerHeader(controller) {
    var header = document.createElement('h1');
    header.className = 'padded';
    header.innerHTML = controller.name + ': Index ' + (controller.index);

    return header;
}

function makeButtonTable(buttons, index) {
    var buttonTable = document.createElement('div');
    buttonTable.className = 'table buttons';
    var buttonTableHead = '<header>\
            <div class="row header">\
                <div>Buttons</div>\
                <div>Pressed</div>\
                <div>Value</div>\
            </div>\
        </header>';
    buttonTable.insertAdjacentHTML('beforeend', buttonTableHead);

    for (var button in buttons) {
        var row = document.createElement('div');
        row.className = 'row';

        var label = document.createElement('div');
        var pressed = document.createElement('div');
        var value = document.createElement('div');

        label.innerHTML = buttons[button].name;

        pressed.id = index + '_' + buttons[button].name;
        pressed.innerHTML = buttons[button].pressed;

        value.id = index + '_' + buttons[button].name + '_value';
        value.innerHTML = buttons[button].value;

        row.appendChild(label);
        row.appendChild(pressed);
        row.appendChild(value);

        buttonTable.appendChild(row);
    }

    return buttonTable;
}

function makeAnalogStickTables(analogSticks, index) {
    var stickWrapper = document.createElement('div');
    stickWrapper.className = 'stick-wrapper';

    for (var stick in analogSticks) {

        var stickTable = document.createElement('div');
        stickTable.className = 'table sticks';

        var stickTableHead = document.createElement('header');
        stickTableHead.className = 'header padded';
        stickTableHead.innerText = analogSticks[stick].name;
        stickTable.appendChild(stickTableHead);

        var positionRow = document.createElement('div');
        positionRow.className = 'row';

        var positionRowSubhead = document.createElement('div');
        positionRowSubhead.className = 'row';

        var labelX = document.createElement('div');
        var labelY = document.createElement('div');

        labelX.innerText = 'Position X';
        labelY.innerText = 'Position Y';

        positionRowSubhead.appendChild(labelX);
        positionRowSubhead.appendChild(labelY);

        var valueX = document.createElement('div');
        var valueY = document.createElement('div');

        valueX.id = index + '_' + analogSticks[stick].name + '_x';
        valueX.innerHTML = analogSticks[stick].position.x;

        valueY.id = index + '_' + analogSticks[stick].name + '_y';
        valueY.innerHTML = analogSticks[stick].position.y;

        positionRow.appendChild(valueX);
        positionRow.appendChild(valueY);

        var angleRow = document.createElement('div');
        angleRow.className = 'row';

        var angleRowSubhead = document.createElement('div');
        angleRowSubhead.className = 'row';

        var labelDeg = document.createElement('div');
        var labelRad = document.createElement('div');

        labelDeg.innerText = 'Degrees';
        labelRad.innerText = 'Radians';

        angleRowSubhead.appendChild(labelDeg);
        angleRowSubhead.appendChild(labelRad);

        var deg = document.createElement('div');
        var rad = document.createElement('div');

        deg.id = index + '_' + analogSticks[stick].name + '_deg';
        deg.innerHTML = (isNaN(analogSticks[stick].angle.degrees)) ? '—' : analogSticks[stick].angle.degrees;

        rad.id = index + '_' + analogSticks[stick].name + '_rad';
        rad.innerHTML = (isNaN(analogSticks[stick].angle.radians)) ? '—' : analogSticks[stick].angle.radians;

        angleRow.appendChild(deg);
        angleRow.appendChild(rad);

        stickTable.appendChild(positionRowSubhead);
        stickTable.appendChild(positionRow);

        var visualisation = '<div class="row padded">\
            <div class="analog-vis" id="' + index + '_' + analogSticks[stick].name + '">\
                <div></div>\
            </div>\
        </div>';
        stickTable.insertAdjacentHTML('beforeend', visualisation);

        stickTable.appendChild(angleRowSubhead);
        stickTable.appendChild(angleRow);

        stickWrapper.appendChild(stickTable);
    }

    return stickWrapper;
}

function showControllerTables(event) {
    if (Controller.controllerCount === 1) {
        document.getElementById('instructions').className = 'hidden';
    }

    var controller = event.detail.controller;

    var wrapper = document.createElement('div');
    wrapper.className = 'controller hidden';
    wrapper.id = 'controller_' + controller.index;

    wrapper.appendChild(makeControllerHeader(controller));
    wrapper.appendChild(makeAnalogStickTables(controller.inputs.analogSticks, controller.index));
    wrapper.appendChild(makeButtonTable(controller.inputs.buttons, controller.index));

    document.querySelector('main').appendChild(wrapper);

    setTimeout(function() {
        wrapper.className = 'controller';
    }, 100);
}


// przyciski
function updateButton(event) {
    var detail = event.detail;

    if (!document.getElementById(detail.controllerIndex + '_' + detail.name)) {
        return;
    }
    document.getElementById(detail.controllerIndex + '_' + detail.name).innerHTML = detail.pressed; // true/ false
    document.getElementById(detail.controllerIndex + '_' + detail.name + '_value').innerHTML = detail.value; //1 lub 0

    if (detail.name == "LEFT_SHOULDER_BOTTOM"){
        websocket.send("LSB__" + detail.value.toFixed(2).toString());
    }
    if (detail.name == "RIGHT_SHOULDER_BOTTOM"){
        websocket.send("RSV__" + detail.value.toFixed(2).toString());
    }

    if (detail.name == "FACE_1"){
        websocket.send("F1___" + detail.value.toFixed(2).toString());
    }
    if (detail.name == "FACE_2"){
        websocket.send("F2___" + detail.value.toFixed(2).toString());
    }
    if (detail.name == "FACE_3"){
        websocket.send("F3___" + detail.value.toFixed(2).toString());
    }
    if (detail.name == "FACE_4"){
        websocket.send("F4___" + detail.value.toFixed(2).toString());
    }

    if (detail.name == "DPAD_UP"){
        websocket.send("D1___" + detail.value.toFixed(2).toString());
    }
    if (detail.name == "DPAD_DOWN"){
        websocket.send("D2___" + detail.value.toFixed(2).toString());
    }
    if (detail.name == "DPAD_LEFT"){
        websocket.send("D3___" + detail.value.toFixed(2).toString());
    }
    if (detail.name == "DPAD_RIGHT"){
        websocket.send("D4___" + detail.value.toFixed(2).toString());
    }

    if (detail.name == "LEFT_SHOULDER"){
        websocket.send("LS___" + detail.value.toFixed(2).toString());
    }
    if (detail.name == "RIGHT_SHOULDER"){
        websocket.send("RS___" + detail.value.toFixed(2).toString());
    }
    if (detail.name == "LEFT_ANALOG_BUTTON"){
        websocket.send("LAB__" + detail.value.toFixed(2).toString());
    }
    if (detail.name == "RIGHT_ANALOG_BUTTON"){
        websocket.send("RAB__" + detail.value.toFixed(2).toString());
    }

    if (detail.name == "START"){
        websocket.send("ST___" + detail.value.toFixed(2).toString());
    }
    if (detail.name == "SELECT"){
        websocket.send("SL___" + detail.value.toFixed(2).toString());
    }
    if (detail.name == "HOME"){
        websocket.send("H____" + detail.value.toFixed(2).toString());
    }

}

///analogi
function updateAnalog(event) {
    var detail = event.detail;

    if (!document.getElementById(detail.controllerIndex + '_' + detail.name + '_x')) {
        return;
    }
    document.getElementById(detail.controllerIndex + '_' + detail.name).querySelector('div').style.transform = 'translate3d(' + (detail.position.x * 50) + 'px, ' + (detail.position.y * 50) + 'px, 0)';
    document.getElementById(detail.controllerIndex + '_' + detail.name + '_x').innerHTML = detail.position.x;
    document.getElementById(detail.controllerIndex + '_' + detail.name + '_y').innerHTML = detail.position.y;
    document.getElementById(detail.controllerIndex + '_' + detail.name + '_deg').innerHTML = (isNaN(detail.angle.degrees)) ? '—' : detail.angle.degrees + '°';
    document.getElementById(detail.controllerIndex + '_' + detail.name + '_rad').innerHTML = (isNaN(detail.angle.radians)) ? '—' : detail.angle.radians;

    if (detail.name == "LEFT_ANALOG_STICK"){
        websocket.send("LAS_X" + detail.position.x.toFixed(2).toString());
        websocket.send("LAS_Y" + detail.position.y.toFixed(2).toString());
    }
    if (detail.name == "RIGHT_ANALOG_STICK"){
        websocket.send("RAS_X" + detail.position.x.toFixed(2).toString());
        websocket.send("RAS_Y" + detail.position.y.toFixed(2).toString());
    }
}



 function onLoad(event) {
    initWebSocket();
  }

  var gateway = `ws://${window.location.hostname}/ws`;
  var websocket;

  window.addEventListener('load', onLoad);

  function initWebSocket() {
    console.log('Trying to open a WebSocket connection...');
    websocket = new WebSocket(gateway);
    websocket.onopen    = onOpen;
    websocket.onclose   = onClose;
  }

  function onOpen(event) {
    console.log('Connection opened');
  }

  function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
  }


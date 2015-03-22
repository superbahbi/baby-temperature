/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
var app = {
    // Application Constructor
    initialize: function() {
        this.bindEvents();
    },
    // Bind Event Listeners
    //
    // Bind any events that are required on startup. Common events are:
    // 'load', 'deviceready', 'offline', and 'online'.
    bindEvents: function() {
        document.addEventListener('deviceready', this.onDeviceReady, false);
    },
    // deviceready Event Handler
    //
    // The scope of 'this' is the event. In order to call the 'receivedEvent'
    // function, we must explicitly call 'app.receivedEvent(...);'
    onDeviceReady: function() {
    var client = new WindowsAzure.MobileServiceClient('url', 'key'),
        todoItemTable = client.getTable('temp');
	var num;
    // Read current data and rebuild UI.
    // If you plan to generate complex UIs like this, consider using a JavaScript templating library.
    function refreshTodoItems() {
        var query = todoItemTable.orderByDescending('__updatedAt').take(1);
        query.read().then(function(todoItems) {
			console.log(todoItems);
			console.log(todoItems.length);
            var listItems = $.map(todoItems, function(item) {
				num = item.temp;
                return  $('#tempdata').html('<h2>' + (Math.round( num * 10 ) / 10) + 'F°</h2>');
            });
			if(num >= 100){ // fever
				 $('.babylogo').css('background-image','url(img/RedBaby.png)');
				 $('.status').html('<strong>Fever</strong>');
			} else if(num > 90 && num < 100){ //hot
				 $('.babylogo').css('background-image','url(img/YellowBaby.png)');
				 $('.status').html('<strong>Hot</strong>');
			} else if(num > 80 && num < 90){ //normal
				 $('.babylogo').css('background-image','url(img/GeenBaby.png)');
				 $('.status').html('<strong>Normal</strong>');
			}else if(num <= 80){
				 $('.babylogo').css('background-image','url(img/BlueBaby.png)');
				 $('.status').html('<strong>Cold</strong>');
			}
            //$('#todo-items').empty().append(listItems).toggle(listItems.length > 0);
            //$('#summary').html('<strong>' + todoItems.length + '</strong>');
        }, handleError);
		
		setTimeout(refreshTodoItems, 5000 );
    }

    function handleError(error) {
        var text = error + (error.request ? ' - ' + error.request.status : '');
        $('#errorlog').append($('<li>').text(text));
    }


    // On initial load, start by fetching the current data
		refreshTodoItems();
        app.receivedEvent('deviceready');
    },
    // Update DOM on a Received Event
    receivedEvent: function(id) {
        var parentElement = document.getElementById(id);
        var listeningElement = parentElement.querySelector('.listening');
        var receivedElement = parentElement.querySelector('.received');

        listeningElement.setAttribute('style', 'display:none;');
        receivedElement.setAttribute('style', 'display:block;');

        console.log('Received Event: ' + id);
    }
};

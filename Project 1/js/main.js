// Create a "close" button and append it to each list item
const fs = require("./FileSaver.js-master");
var data = '{"robo":[{"minute": "urgency"}]}';
var myNodelist = document.getElementsByTagName("LI");
var i;
for (i = 0; i < myNodelist.length; i++) {
  var span = document.createElement("SPAN");
  var txt = document.createTextNode("\u00D7");
  span.className = "close";
  span.appendChild(txt);
  myNodelist[i].appendChild(span);
}

// Click on a close button to hide the current list item
var close = document.getElementsByClassName("close");
var i;
for (i = 0; i < close.length; i++) {
  close[i].onclick = function() {
    var div = this.parentElement;
    div.style.display = "none";
  }
}

// Add a "checked" symbol when clicking on a list item
var list = document.querySelector('ul');
list.addEventListener('click', function(ev) {
  if (ev.target.tagName === 'LI') {
    ev.target.classList.toggle('checked');
  }
}, false);

// Create a new list item when clicking on the "Add" button
function newElement() {
  var li = document.createElement("li");
  const inputValue = document.getElementById("myInput").value;
  var x = document.getElementById("myInput3").value, y = document.getElementById("myInput4").value;
  var test = document.getElementById("myUL")
  function Urgency(x, y, inputValue, test) { 
		var z = x + y
		//console.log(x, "x")
		//console.log(y, "y")
		if (test === undefined) {
			 console.log("test")
			 var t = document.createTextNode(inputValue); //
			 li.appendChild(t); //
			 //above is fine
			 document.getElementById("myUL").appendChild(li);

		} else if ( y == 1) {
			console.log("test2")
			 var t = document.createElement("li"); //
			 var textnode = document.createTextNode(inputValue);
			 t.appendChild(textnode)
			 var w = li.appendChild(t); //
			 var l = document.getElementById("myUL");
			 //var w = document.getElementById("myUL").appendChild(li);
			 var og = document.getElementById("right");
			 //og.insertBefore(w, l.firstChild)
			 l.insertBefore(w, l.firstChild)
		} else if (y == 3){
			console.log("test2")
			 var t = document.createElement("li"); //
			 var textnode = document.createTextNode(inputValue);
			 t.appendChild(textnode)
			 var w = li.appendChild(t); //
			 var l = document.getElementById("myUL");
			 //var w = document.getElementById("myUL").appendChild(li);
			 var og = document.getElementById("right");
			 //og.insertBefore(w, l.firstChild)
			 l.insertBefore(w, l.lastChild)
			
		} else {
			console.log("test 3")
			 var t = document.createElement("li"); //
			 var textnode = document.createTextNode(inputValue);
			 t.appendChild(textnode)
			 var w = li.appendChild(t); //
			 var l = document.getElementById("myUL");
			 //var w = document.getElementById("myUL").appendChild(li);
			 var og = document.getElementById("right");
			 //og.insertBefore(w, l.firstChild)
			 var input = (l.children.length/2)
			 if (input < 1) { l.insertBefore(1, l.firstChild) } else {
					l.insertBefore(w, l.childNodes[input])
			 }
		}

	}
  if (inputValue === '') {
    alert("You must write something!");
  } else {
	Urgency(x, y, inputValue, test)
  }
  document.getElementById("myInput").value = "testing";

  var span = document.createElement("SPAN");
  var txt = document.createTextNode("\u00D7");
  span.className = "close";
  span.appendChild(txt);
  li.appendChild(span);

  for (i = 0; i < close.length; i++) {
    close[i].onclick = function() {
      var div = this.parentElement;
      div.style.display = "none";
    }
  }
  
  function fileDownload(data) {
	fs.writeFile("data.txt", data ,"utf-8", (err) => {
	  if (err) {throw err;}
  })  
	  
  }
  
  var data = data['Robo'].push("minute": myInput3)
  var data = data['Robo'].push("urgency": myInput4)
  fileDownload(data);
  
  
}

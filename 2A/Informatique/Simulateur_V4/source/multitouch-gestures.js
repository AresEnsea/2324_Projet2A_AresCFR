let evCache = [];

function initGestures() {
    // Install event handlers for the pointer target
    var el = document.getElementById("defaultCanvas0");
    el.onpointerdown = pointerdownHandler;
    el.onpointermove = pointermoveHandler;

    // Use same handler for pointer{up,cancel,out,leave} events since
    // the semantics for these events - in this app - are the same.
    el.onpointerup = pointerupHandler;
    el.onpointercancel = pointerupHandler;
    el.onpointerout = pointerupHandler;
    el.onpointerleave = pointerupHandler;
}

function pointerdownHandler(ev) {
    // The pointerdown event signals the start of a touch interaction.
    // This event is cached to support 2-finger gestures
    evCache.push(ev);
    console.log("pointerDown", ev);
}

function pointermoveHandler(ev) {
    // This function implements a 2-pointer horizontal pinch/zoom gesture.
    //
    // If the distance between the two pointers has increased (zoom in),
    // the target element's background is changed to "pink" and if the
    // distance is decreasing (zoom out), the color is changed to "lightblue".
    //
    // This function sets the target element's border to "dashed" to visually
    // indicate the pointer's target received a move event.
    // console.log("pointerMove", ev);
    ev.target.style.border = "dashed";

    // Find this event in the cache and update its record with this event
    for (var i = 0; i < evCache.length; i++) {
        if (ev.pointerId == evCache[i].pointerId) {
            evCache[i] = ev;
            break;
        }
    }

    // If two pointers are down, check for pinch gestures
    if (evCache.length == 2) {
        // Calculate the distance between the two pointers
        var curDiff = Math.abs(evCache[0].clientX - evCache[1].clientX);

        if (prevDiff > 0) {
            if (curDiff > prevDiff) {
                // The distance between the two pointers has increased
                console.log("Pinch moving OUT -> Zoom in", ev);
                ev.target.style.background = "pink";
            }
            if (curDiff < prevDiff) {
                // The distance between the two pointers has decreased
                console.log("Pinch moving IN -> Zoom out", ev);
                ev.target.style.background = "lightblue";
            }
        }

        // Cache the distance for the next move event
        prevDiff = curDiff;
    }
}

function pointerupHandler(ev) {
    console.log(ev.type, ev);
    // Remove this pointer from the cache and reset the target's
    // background and border
    removeEvent(ev);
    ev.target.style.background = "white";
    ev.target.style.border = "1px solid black";

    // If the number of pointers down is less than two then reset diff tracker
    if (evCache.length < 2) {
        prevDiff = -1;
    }
}

function removeEvent(ev) {
    // Remove this event from the target's cache
    for (var i = 0; i < evCache.length; i++) {
      if (evCache[i].pointerId == ev.pointerId) {
        evCache.splice(i, 1);
        break;
      }
    }
   }
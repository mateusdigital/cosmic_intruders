
var Module = null;

function
Initialize_Ems()
{
    console.log("CLICKED");
    document.getElementById('loadingDiv').innerHTML = "Loading, please wait...";

    Module = {
        onRuntimeInitialized: function() {
            document.getElementById('Div_CanvasContainer').style.visibility = "visible";
            document.getElementById('loadingDiv').style.visibility = "hidden";
        },

        canvas: (function() {
            var canvas = document.getElementById('canvas');
                return canvas;
            })()
    };


    (function() {
        var memoryInitializer = 'CosmicIntruders.html.mem';
        if (typeof Module['locateFile'] === 'function') {
            memoryInitializer = Module['locateFile'](memoryInitializer);
        } else if (Module['memoryInitializerPrefixURL']) {
            memoryInitializer = Module['memoryInitializerPrefixURL'] + memoryInitializer;
        }

        var xhr = Module['memoryInitializerRequest'] = new XMLHttpRequest();
        xhr.open('GET', memoryInitializer, true);
        xhr.responseType = 'arraybuffer';
        xhr.send(null);
    })();

    var script = document.createElement('script');
    script.src = "CosmicIntruders.js";
    document.body.appendChild(script);
}


document.getElementById("play_button").onclick = Initialize_Ems;

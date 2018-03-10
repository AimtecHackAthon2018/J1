<script src="https://cak.zcu.cz:9444/speechcloud.js" type="text/javascript"></script>
<script>
  document.addEventListener("DOMContentLoaded", function() {
      let ASR_GRAMMAR = `#ESGF V1.0 UTF-8 cs;
        grammar gramatika;
        public <gramatika> = (
            <slova>
        )*;
        <slova> = (
            Dopředu | Dozadu | Doprava | Doleva {vlevo}| Levá {vlevo} | Stůj | Blikej | Zhasni | Nákup | Nabít | Dojeď pro rohlíky | Pivo
        );
      `;

      let sc_options = {
          uri: "https://cak.zcu.cz:9443/v1/speechcloud/edu-hofmann",
          tts: '#ttsaudio'
      };
      // create instance
      let speechCloud = new SpeechCloud(sc_options);
      let logElm = document.getElementById('log');

      recordVoice = false;
      numberLines = 10;

      function logInPage(text) {
        var N =   $('.lineCommand').length - numberLines;
        var out = "";

        $('.lineCommand').each(function(index){
            N = N - 1;
            if (N<0) {
              out = out + "<span class=\"lineCommand\" style=\"display:block\">" + $(this).text() + "</span>";
            }
        });

        out = out + "<span class=\"lineCommand\" style=\"display:block\">" + text + "</span>";

        $("#log").html(out);

        // logElm.innerHTML = logElm.innerHTML + "<span class=\"lineCommand\" style=\"inline-block\">" + text + "</span>" + "\n";
      }

      // asr is initialized, time to set a grammar
      speechCloud.on("asr_initialized", function() {
          // set ASR grammar, only ESGF format is allowed
          speechCloud.asr_set_grammar({grammar:ASR_GRAMMAR, grammar_type:"esgf"});
      });
      // asr is ready and recognition can be started
      speechCloud.on("asr_ready", function () { // set SLU grammar
          //speechCloud.slu_set_grammars({grammars: GRAMMARS, process_partial_results: false, process_final_results: true});
          speechCloud.tts_synthesize({text: "Ahoj Miči tady Kit.", voice: "Stanislav26"});


          $( "#startVoiceBtn" ).on('click',function() {
            if (!recordVoice) {
              recordVoice = true;
              speechCloud.asr_recognize();
              $(this).removeClass('btn-primary').addClass('btn-danger').html('<i class="fa fa-microphone-slash" style="font-size:24px"></i> Record');
            } else {
              recordVoice = false;
              speechCloud.asr_pause();
              $(this).removeClass('btn-danger').addClass('btn-primary').html('<i class="fa fa-microphone" style="font-size:24px"></i> Record');
            }
          });
      });


      // event with recognition results
      speechCloud.on("asr_result", function (e) {
          speechCloud.asr_pause();
          console.log(e);

          logInPage(e.word_1best);

          var bestSlova = e.word_1best;

          if (bestSlova.includes("Pivo")) {
          }
      });

      // event with results from spoken language understanding
      speechCloud.on("slu_entities", function (e) {
          if (!e.partial_result) { // partial results can be used, but we ignore them
              // ....... handle slu
          }

      });

      // event with detected signal
      speechCloud.on("asr_signal", function (e) {
          console.log(e);
      });

      // recognition stopped
      speechCloud.on("asr_paused", function(e) {
          // .....
      });

      // something went wrong
      speechCloud.on('sc_error', function (msg) {
          console.error(msg);
      });
      // text-to-speech finished
      speechCloud.on('tts_done', function (e) {
          //speechCloud.asr_recognize(); // start recognition
      });

      // handlers are set, we can initialize speechCloud
      speechCloud.init();
  });
</script>


<div class="jumbotron">
<div class="container">
  <h1 class="display-3">SpeechCloud</h1>

  <div class="row mb-2">
    <div class="col-md-8">
      <div class="card">
        <div id="log" class="card-body small" style="height:250px;"></div>
      </div>
    </div>

    <div class="col-md-4">
      <h2 class="display-7">Ovládnání:</h2>
      <button type="button" id="startVoiceBtn" class="btn btn-primary"><i class="fa fa-microphone" style="font-size:24px"></i> Record</button>
    </div>
  </div>

  <!-- needed for TTS -->
  <audio id="ttsaudio"></audio>

</div>
</div>

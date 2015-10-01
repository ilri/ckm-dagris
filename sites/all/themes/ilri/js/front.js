(function ($) {
$(document).ready(function(){
  // Init Skrollr
    var s = skrollr.init({
        render: function(data) {
            //Debugging - Log the current scroll position.
            //console.log(data.curTop);
        }
    });

  // Slide 2
  $("#slide-2 .main.entities a").click(function(e){
    e.preventDefault();
    $(this).siblings('.active').removeClass('active');
    $(this).addClass('active');
    var show_id = $(this).data('show');
    $('#slide-2 .details').children().hide();
    $(show_id).slideDown("slow");
  });

});
}(jQuery));

(function ($) {
  Drupal.d3.dagris_bar = function (select, settings) {

    var data =  settings.rows;
    var labels = data.map(function(d) { return String(d[1]); });
    var label_values = data.map(function(d){ return d[0]; });
    var values = data.map(function(d){ return d[0].replace(/,/g, ""); });
    var margin = {"top": 50, "right": 10, "bottom": 30, "left": 50}, width = 800, barHeight = 50;

     var svg_container_id = "report-" + new Date().getTime();
    $("div.d3.dagris_bar.d3-processed").append("<div id='" + svg_container_id +"'></div>");

    var x = d3.scale.linear()
    .range([0, width]);

    var chart = d3.select("#" + svg_container_id).append("svg")
        .attr("width", width);

    x.domain([0, d3.max(values, function(d){ return +d; })]);

    chart.attr("height", barHeight * values.length + 30);

    var bar = chart.selectAll("g")
      .data(values)
    .enter().append("g")
      .attr("transform", function(d, i) { return "translate(150," + i * barHeight + ")"; });

    bar.append("rect")
      .attr("width", function(d) { return x(d); })
      .attr("height", barHeight - 3)
      .append("title")
        .html(function(d) { return d + " Entries"; });

    bar.append("text")
      .attr("x", -3)
      .attr("y", barHeight / 2)
      .attr("dy", ".35em")
      .text(function(d, i) { return labels[i]; });

    chart.append("g")
      .attr("transform", "translate(150,0"+ (barHeight * values.length - 15) +")")
      .append("text")
      .attr("class", "total")
      .attr("y", 6)
      .attr("dy", "1.5em")
      .attr("font-size", ".8em")
      .text("Total Records: " + d3.sum(values));

  }
})(jQuery);

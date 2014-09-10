(function ($) {
  Drupal.d3.dagris = function (select, settings) {
  var data =  settings.rows;
  var labels = data.map(function(d) { return String(d[1]); });
  var values = data.map(function(d){ return d[0]; });
  var margin = {"top": 50, "right": 10, "bottom": 30, "left": 50}, width = 400, height = 300;

  var width = 848,
  height = 300,
  radius = Math.min(width, height) / 2;

  var color = d3.scale.category20c();

  var arc = d3.svg.arc()
  .outerRadius(radius - 10)
  .innerRadius(0);

  var pie = d3.layout.pie()
  .sort(null)
  .value(function(d) { return d; });

  var svg_container_id = "report-" + new Date().getTime();
  $("div.d3.dagris.d3-processed").append("<div id='" + svg_container_id +"'></div>");

  var svg = d3.select("#" + svg_container_id).append("svg")
  .attr("id", "question-piechart")
  .attr("width", width + margin.left + margin.right)
  .attr("height", height + margin.top + margin.bottom)
  .append("g")
  .attr("transform", "translate(" + (width + margin.left + margin.right) / 4 + "," + (height + margin.top + margin.bottom) / 2 + ")");

  var g = svg.selectAll(".arc")
  .data(pie(values))
  .enter()
   .append("g")
   .attr("class", "arc");

  g.append("path")
  .attr("d", arc)
  .attr("data-title", function(d, i) {return labels[i] + " - " + (((values[i]/d3.sum(values))*100).toFixed(2)) + "%"; })
  .style("fill", function(d, i) { return color(i); })
  .append("title")
   .text(function(d, i) { return labels[i] + " - " + values[i]; });

  var legend = d3.select("#" + svg_container_id + " svg").append("g")
  .attr("class", "legend")
  .attr("width", radius * 2)
  .attr("height", radius * 2)
  .selectAll("g")
  .data(values)
  .enter().append("g")
  .attr("transform", function(d, i) { return "translate(" +  (width - 300) + "," + (i + 3) * 20 + ")"; });

  legend.append("rect")
  .attr("width", 18)
  .attr("height", 18)
  .style("fill", function(d, i) { return color(i); });

  legend.append("text")
  .attr("x", 24)
  .attr("y", 9)
  .attr("dy", ".35em")
  .text(function(d, i) { return labels[i] + " - " + values[i]; });

  d3.select("#" + svg_container_id + " svg#question-piechart")
  .append("g")
  .attr("transform", "translate(0,"+ (height + 30) +")")
  .append("text")
  .attr("y", 6)
  .attr("dy", "1.5em")
  .attr("font-size", ".8em")
  .text("Total Records: " + d3.sum(values));



  }
})(jQuery);

<html>
<head>
 <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="description" content="">
    <meta name="author" content="">

    <!-- Bootstrap Core CSS -->
    <link href="css/bootstrap.min.css" rel="stylesheet">

    <!-- Custom CSS -->
    <link href="css/one-page-wonder.css" rel="stylesheet">

	<title>Crime Hotspot Detection - Implementation</title>
  <script src="http://maps.google.com/maps/api/js?key=AIzaSyCgYcBRh42V_jheXD9-DAZrQdJ2snKmlLo&sensor=false" type="text/javascript"></script>
</head>
<body>
<?php
$row = 0;
$i=0;$j=0;
if (($handle = fopen("england.csv", "r")) !== FALSE) {
    while (($data = fgetcsv($handle, 1000, ",")) !== FALSE) {
        $num = count($data);
		
        if($row!=0)
		{
			$loc[$row-1][0]=$data[5];
			$loc[$row-1][1]=$data[4];
			$loc[$row-1][2]=$data[9];
			
		}
		$row++;
			/*if($row==10)
		{break;}*/
    }
    fclose($handle);
}

$filecontents = file_get_contents('outt2.txt');

$words = preg_split('/[\s]+/', $filecontents, -1, PREG_SPLIT_NO_EMPTY);
$i=0;$j=0;
foreach($words as $word){
	//print($word."<br>");
	$hspt[$i][$j]=$word;
	//echo $loc[$i][$j]."<br>"; 
	$j+=1;
	if($j==2)
	{$i+=1;$j=0;}
}



?>








  
  
  <nav class="navbar navbar-inverse navbar-fixed-top" role="navigation">
        <div class="container">
            <!-- Brand and toggle get grouped for better mobile display -->
            <div class="navbar-header">
                <button type="button" class="navbar-toggle" data-toggle="collapse" data-target="#bs-example-navbar-collapse-1">
                    <span class="sr-only">Toggle navigation</span>
                    <span class="icon-bar"></span>
                    <span class="icon-bar"></span>
                    <span class="icon-bar"></span>
                </button>
                <a class="navbar-brand" href="#">Home</a>
            </div>
            <!-- Collect the nav links, forms, and other content for toggling -->
            <div class="collapse navbar-collapse" id="bs-example-navbar-collapse-1">
                <ul class="nav navbar-nav">
					<li>
						<a href="#showmap">Show Map</a>
                    </li>
					<li>
                        <a href="#about">Circular</a>
                    </li>
                    <li>
                        <a href="newring.php">Ring</a>
                    </li>
                    <li>
                        <a href="#contact">Linear</a>
                    </li>
                    <li>
                        <a href="#contact">About</a>
                    </li>
                </ul>
            </div>
            <!-- /.navbar-collapse -->
        </div>
        <!-- /.container -->
    </nav>
    <!-- Full Width Image Header -->
    <header class="header-image" style="background:url('img.jpg'); height:80%; width:100%; align: center;">
        <div class="headline">
            <div class="container" ">
                <h2>Crime Hotspot Detection</h2>
				<br>
                <h2>A Computational Perspective</h2>
            </div>
        </div>
    </header>
	
	<hr>


		
    <!-- Page Content -->
    <div class="container">
	
	
        	<div class="featurette" id="showmap">
        
				<div class="row" >
					<div class="col-md-2"> </div>
					<div class="col-md-8" id="map" style="height: 100%; width: 100%;"> </div>
					<div class="col-md-2" style="color:#999;"> </div>
				</div>

			</div>
			
			
        <hr class="featurette-divider">

        <!-- First Featurette 
        <div class="featurette" id="about">
            <img class="featurette-image img-circle img-responsive pull-right" src="http://placehold.it/500x500">
            <h2 class="featurette-heading">This First Heading
                <span class="text-muted">Will Catch Your Eye</span>
            </h2>
            <p class="lead">Donec ullamcorper nulla non metus auctor fringilla. Vestibulum id ligula porta felis euismod semper. Praesent commodo cursus magna, vel scelerisque nisl consectetur. Fusce dapibus, tellus ac cursus commodo.</p>
        </div>

        <hr class="featurette-divider">

        <!-- Second Featurette 
        <div class="featurette" id="services">
            <img class="featurette-image img-circle img-responsive pull-left" src="http://placehold.it/500x500">
            <h2 class="featurette-heading">The Second Heading
                <span class="text-muted">Is Pretty Cool Too.</span>
            </h2>
            <p class="lead">Donec ullamcorper nulla non metus auctor fringilla. Vestibulum id ligula porta felis euismod semper. Praesent commodo cursus magna, vel scelerisque nisl consectetur. Fusce dapibus, tellus ac cursus commodo.</p>
        </div>

        <hr class="featurette-divider">

        <!-- Third Featurette 
        <div class="featurette" id="contact">
            <img class="featurette-image img-circle img-responsive pull-right" src="http://placehold.it/500x500">
            <h2 class="featurette-heading">The Third Heading
                <span class="text-muted">Will Seal the Deal.</span>
            </h2>
            <p class="lead">Donec ullamcorper nulla non metus auctor fringilla. Vestibulum id ligula porta felis euismod semper. Praesent commodo cursus magna, vel scelerisque nisl consectetur. Fusce dapibus, tellus ac cursus commodo.</p>
        </div>

        <hr class="featurette-divider">

        <!-- Footer -->
        <footer>
            <div class="row">
                <div class="col-lg-12">
                    <p>Copyright &copy; 2017 Minor Project Team</p>
                </div>
            </div>
        </footer>

    </div>
    <!-- /.container -->

    <!-- jQuery -->
    <script src="js/jquery.js"></script>

    <!-- Bootstrap Core JavaScript -->
    <script src="js/bootstrap.min.js"></script>



</body>




<script type="text/javascript">
 
	var locations=<?php echo json_encode($loc );?>;
	var hotspot=<?php echo json_encode($hspt );?>;

    var map = new google.maps.Map(document.getElementById('map'), {
      zoom: 13,
      center: new google.maps.LatLng(51.5266 ,-0.194924),
      mapTypeId: google.maps.MapTypeId.ROADMAP
    });

    var infowindow = new google.maps.InfoWindow();

    var marker, i;

    for (i = 0; i < locations.length; i++) { 
		var image = "https://storage.googleapis.com/support-kms-prod/SNP_2752068_en_v0";
		var icon = {
			url: "https://storage.googleapis.com/support-kms-prod/SNP_2752068_en_v0", // url
			scaledSize: new google.maps.Size(6, 6), // scaled size
			origin: new google.maps.Point(0,0), // origin
			anchor: new google.maps.Point(0, 0) // anchor
		};
		
		if(locations[i][2]=="Anti-social behaviour"||locations[i][2]=="Drugs"||locations[i][2]=="Public order"||locations[i][2]=="Violence and sexual offences"||locations[i][2]=="Other crime")
		{var marker = new google.maps.Marker({
        position: new google.maps.LatLng(locations[i][0], locations[i][1]),
        map: map,
        icon: icon
});
      google.maps.event.addListener(marker, 'click', (function(marker, i) {
        return function() {
          infowindow.setContent(locations[i][2]);
          infowindow.open(map, marker);
        }
      })(marker, i));
    }
	}
	
	for (i = 0; i < hotspot.length; i++) { 
	
		
		var image = "https://storage.googleapis.com/support-kms-prod/SNP_2752125_en_v0";
		var marker = new google.maps.Marker({
        position: new google.maps.LatLng(hotspot[i][0], hotspot[i][1]),
        map: map,
        icon: image
});

	google.maps.event.addListener(marker, 'click', (function(marker, i) {
        return function() {
          infowindow.setContent(hotspot[i][0]+"  "+hotspot[i][1]+"");
          infowindow.open(map, marker);
        }
      })(marker, i));
	  

	var circle = new google.maps.Circle({
		map: map,
		radius: 2500,		// 10 miles in metres
		    fillColor: '#f75959',
            fillOpacity: 0.3,
			strokeColor: "#f75959",
            strokeWidth: 5
			
		});
circle.bindTo('center', marker, 'position');
    }
	
  </script>
</html>

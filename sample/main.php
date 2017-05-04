<?PHP

require_once 'Color.class.php';
require_once 'Vertex.class.php';
require_once 'Vector.class.php';
require_once 'Matrix.class.php';
require_once 'Camera.class.php';

$origin = new Vertex(array('x' => 0.0, 'y' => 0.0, 'z' => 0.0));
$pt = new Vertex(array('x' => 42.0, 'y' => 42.0, 'z' => 42.0));

$cam = New Camera(array(
			'origin' => new Vertex(array('x' => 15.0, 'y' => 15.0, 'z' => 80.0)),
			'orientation' => new Matrix(array('preset' => Matrix::RY, 'angle' => M_PI)),
			'width' => 640.0, 'height' => 480.0, 'fov' => 60.0,
			'near' => 1.0, 'far' => 100.0));
print $origin.PHP_EOL;
$origin = $cam->watchVertex($origin);
print $origin.PHP_EOL.PHP_EOL;

print $pt.PHP_EOL;
$pt = $cam->watchVertex($pt);
print $pt.PHP_EOL;

?>

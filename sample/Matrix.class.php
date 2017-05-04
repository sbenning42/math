<?PHP

require_once 'Vector.class.php';

Class Matrix {

	const IDENTITY = "IDENTITY";
	const SCALE = "SCALE preset"; 
	const RX = "Ox ROTATION preset";
	const RY = "Oy ROTATION preset";
	const RZ = "Oz ROTATION preset";
	const TRANSLATION = "TRANSLATION preset";
	const PROJECTION = "PROJECTION preset";

	public static $verbose = FALSE;

	public static function doc() {
		print (file_get_contents("./Matrix.doc.txt") . PHP_EOL);
		return;
	}

	private $_matrix = array(array(1, 0, 0, 0), array(0, 1, 0, 0), array(0, 0, 1, 0), array(0, 0, 0, 1) );

	public function transpose() {
		$old_verbose = Matrix::$verbose;
		Matrix::$verbose = false;
		$result = new Matrix( ['preset' => Matrix::IDENTITY] );
		Matrix::$verbose = $old_verbose;
		for ( $i = 0; $i < 4; $i++ ) {
			for ( $j = 0; $j < 4; $j++ )
				$result->_matrix[$i][$j] = $this->_matrix[$j][$i];
		}
		return ( $result );	
	}

	public function mult( $rhs ) {
		$old_verbose = Matrix::$verbose;
		Matrix::$verbose = false;
		$result = new Matrix( ['preset' => Matrix::IDENTITY] );
		Matrix::$verbose = $old_verbose;
		for ( $i = 0; $i < 4; $i++ ) {
			for ( $j = 0; $j < 4; $j++ )
				$result->_matrix[$i][$j] = $this->_matrix[$i][0] * $rhs->_matrix[0][$j] + $this->_matrix[$i][1] * $rhs->_matrix[1][$j] + $this->_matrix[$i][2] * $rhs->_matrix[2][$j] + $this->_matrix[$i][3] * $rhs->_matrix[3][$j];
		}
		return ( $result );
	}
	
	public function transformVertex( Vertex $vtx ) {
		$x = $vtx->getX() * $this->_matrix[0][0] + $vtx->getY() * $this->_matrix[0][1] + $vtx->getZ() * $this->_matrix[0][2] + $this->_matrix[0][3];
		$y = $vtx->getX() * $this->_matrix[1][0] + $vtx->getY() * $this->_matrix[1][1] + $vtx->getZ() * $this->_matrix[1][2] + $this->_matrix[1][3];
		$z = $vtx->getX() * $this->_matrix[2][0] + $vtx->getY() * $this->_matrix[2][1] + $vtx->getZ() * $this->_matrix[2][2] + $this->_matrix[2][3];
		$w = $vtx->getX() * $this->_matrix[3][0] + $vtx->getY() * $this->_matrix[3][1] + $vtx->getZ() * $this->_matrix[3][2] + $this->_matrix[3][3];
		return (new Vertex(['x' => $x / $w, 'y' => $y / $w, 'z' => $z / $w, 'color' => $vtx->getColor() ]));
	}

	public function transformTriangle( $Triangle ) {
		$tA = $this->transformVertex( $Triangle->getA() );
		$tB = $this->transformVertex( $Triangle->getB() );
		$tC = $this->transformVertex( $Triangle->getC() );
		return ( new Triangle( $tA, $tB, $tC ) );
	}

	public function transformMesh( $Mesh ) {
		foreach( $Mesh as $Triangle )
			$return[] = $this->transformTriangle( $Triangle );
		return( $return );
	}
	private function _create_scale( $nb ) {
		$this->_matrix[0][0] = $nb;
		$this->_matrix[1][1] = $nb;
		$this->_matrix[2][2] = $nb;
		return;
	}
	
	private function _create_rotate( $type, $angle ) {
		if ($type == self::RX)
		{
			$this->_matrix[1][1] = cos( $angle );
			$this->_matrix[1][2] = -sin( $angle );
			$this->_matrix[2][1] = sin( $angle );
			$this->_matrix[2][2] = cos( $angle );
			return;
		}
		else if ($type == self::RY)
		{
			$this->_matrix[0][0] = cos( $angle );
			$this->_matrix[0][2] = sin( $angle );
			$this->_matrix[2][0] = -sin( $angle );
			$this->_matrix[2][2] = cos( $angle );
			return;
		}
		else if ($type == self::RZ)
		{
			$this->_matrix[0][0] = cos( $angle );
			$this->_matrix[0][1] = -sin( $angle );
			$this->_matrix[1][0] = sin( $angle );
			$this->_matrix[1][1] = cos( $angle );
			return;
		}
		return;
	}
	
	private function _create_translate( Vector $vtc ) {
		$this->_matrix[0][3] += $vtc->getX();
		$this->_matrix[1][3] += $vtc->getY();
		$this->_matrix[2][3] += $vtc->getZ();
		return;
	}
	
	private function _OpenGLPerspective( $fov, $ratio, $near, $far) {
		$scale = tan(deg2rad($fov * 0.5)) * $near;
		$right = $ratio * $scale;
		$left = -$right;
		$top = $scale;
		$bottom = -$top;
		self::_OpenGLFrustrum($left, $right, $bottom, $top, $near, $far);
	}

	private function _OpenGLFrustrum($left, $right, $bottom, $top, $near, $far) {
		$this->_matrix[0][0] = (2 * $near) / ($right - $left);
		$this->_matrix[0][1] = 0;
		$this->_matrix[0][2] = ($right + $left) / ($right - $left);
		$this->_matrix[0][3] = 0;

		$this->_matrix[1][0] = 0;
		$this->_matrix[1][1] = (2 * $near) / ($top - $bottom);
		$this->_matrix[1][2] = ($top + $bottom) / ($top - $bottom);
		$this->_matrix[1][3] = 0;

		$this->_matrix[2][0] = 0;
		$this->_matrix[2][1] = 0;
		$this->_matrix[2][2] = -(($far + $near) / ($far - $near));
		$this->_matrix[2][3] = -((2 * $far * $near) / ($far - $near));

		$this->_matrix[3][0] = 0;
		$this->_matrix[3][1] = 0;
		$this->_matrix[3][2] = -1;
		$this->_matrix[3][3] = 0;
	}
	
	public function __construct( array $kwargs ) {
		if ( !array_key_exists('preset', $kwargs ) )
			return;
		if ( self::$verbose == TRUE )
			print('Matrix ' . $kwargs['preset'] . ' instance constructed' . PHP_EOL);	
		if ( $kwargs['preset'] == self::IDENTITY )
			return ;
		else if ( $kwargs['preset'] == self::SCALE && array_key_exists( 'scale', $kwargs ) )
			$this->_create_scale( $kwargs['scale'] );
		else if ( $kwargs['preset'] == self::RX || $kwargs['preset'] == self::RY || $kwargs['preset'] == self::RZ && array_key_exists( 'angle', $kwargs ) )
			$this->_create_rotate( $kwargs['preset'], $kwargs['angle'] );
		else if ( $kwargs['preset'] == self::TRANSLATION && array_key_exists( 'vtc', $kwargs ) )
			$this->_create_translate( $kwargs['vtc'] );
		else if ( $kwargs['preset'] == self::PROJECTION && array_key_exists( 'fov', $kwargs ) && array_key_exists( 'ratio', $kwargs ) && array_key_exists( 'near', $kwargs ) && array_key_exists( 'far', $kwargs ) )
			$this->_OpenGLPerspective( $kwargs['fov'], $kwargs['ratio'], $kwargs['near'], $kwargs['far'] );
	return;
	}

	public function __destruct() {
		if ( self::$verbose == TRUE )
			print('Matrix instance destructed' . PHP_EOL);
		return;
	}

	public function __toString() {
		return (sprintf('M | vtcX | vtcY | vtcZ | vtxO' . PHP_EOL . '-----------------------------' . PHP_EOL . 'x | %.2f | %.2f | %.2f | %.2f' . PHP_EOL . 'y | %.2f | %.2f | %.2f | %.2f' . PHP_EOL . 'z | %.2f | %.2f | %.2f | %.2f' . PHP_EOL . 'w | %.2f | %.2f | %.2f | %.2f', $this->_matrix[0][0], $this->_matrix[0][1], $this->_matrix[0][2], $this->_matrix[0][3], $this->_matrix[1][0], $this->_matrix[1][1], $this->_matrix[1][2], $this->_matrix[1][3], $this->_matrix[2][0], $this->_matrix[2][1], $this->_matrix[2][2], $this->_matrix[2][3], $this->_matrix[3][0], $this->_matrix[3][1], $this->_matrix[3][2], $this->_matrix[3][3] ) );
	}
}

?>

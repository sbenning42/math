<?PHP

Class Triangle {

	public static $verbose = FALSE;

	public static function doc() {
		print (file_get_contents("./Vector.doc.txt"));
		return;
	}

	private $_A;
	private $_B;
	private $_C;
	private $_visiblei = false;

	public function getA() {
		return ( clone $this->_A );
	}

	public function getB() {
		return ( clone $this->_B );
	}

	public function getC() {
		return ( clone $this->_C );
	}

	public function getVisibility() {
		return $this->_visible;
	}

	public function setVisibility( $val ) {
		$this->_visible = $val;
	}

	public function getNormal() {
		$vec1 = new Vector( ['dest' => $this->getB(), 'orig' => $this->getA()] ); 
		$vec2 = new Vector( ['dest' => $this->getC(), 'orig' => $this->getA()] );
		return ( $vec1->crossProduct( $vec2 ) );
	}

	public function getCentroid() {
		$x = ( $this->_A->getX() + $this->_B->getX() + $this->_C->getX() ) / 3;
		$y = ( $this->_A->getY() + $this->_B->getY() + $this->_C->getY() ) / 3;
	   	$z = ( $this->_A->getZ() + $this->_B->getZ() + $this->_C->getZ() ) / 3; 	
		return( new Vertex( ['x' => round($x), 'y' => round($y), 'z' => round($z) ] ) );
	}

	public function area() {
		$ax = $this->_A->getX();
		$ay = $this->_A->getY();
		$bx = $this->_B->getX();
		$by = $this->_B->getY();
		$cx = $this->_C->getX();
		$cy = $this->_C->getY();
		$area = abs( ( $ax * ( $by - $cy ) + $bx * ( $cy - $ay ) + $cx * ( $ay - $by ) ) / 2 );
		return ( $area);
	}

	public function get_point_color( Vertex $p ) {
		$abp = new Triangle( $this->_A, $this->_B, $p );
		$acp = new Triangle( $this->_A, $this->_C, $p );
		$bcp = new Triangle( $this->_B, $this->_C, $p );
		$t_area = $this->area();
		$a_area = $bcp->area();
		$b_area = $acp->area();
		$c_area = $abp->area();
		return ( Color::trifusion( $this->_A->getColor(), $a_area / $t_area, $this->_B->getColor(), $b_area / $t_area, $this->_C->getColor(), $c_area / $t_area ) );
	}

	public function __construct( $A, $B, $C ) {
		if ( !$A || !$C || !$B  )
			return;
		$this->_A = clone $A;
		$this->_B = clone $B;
		$this->_C = clone $C;
		if (self::$verbose == TRUE)
			printf( 'Triangle constructed.' );
		return;
	}

	public function __destruct() {
		if (self::$verbose == TRUE)
			printf( 'Triangle destructed' );
		return;
	}

}

?>

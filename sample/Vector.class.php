<?PHP
require_once 'Vertex.class.php';

Class Vector {

	public static $verbose = FALSE;

	public static function doc() {
		print (file_get_contents("./Vector.doc.txt"));
		return;
	}

	private $_x;
	private $_y;
	private $_z;
	private $_w = 0;
	
	public function getX() { return $this->_x; }
	public function getY() { return $this->_y; }
	public function getZ() { return $this->_z; }
	public function getW() { return $this->_w; }
	
	public function __construct( array $kwargs ) {
		if ( !array_key_exists('dest', $kwargs) )
			return;
		if ( !array_key_exists( 'orig', $kwargs ) )
			$kwargs['orig'] = new Vertex( array('x' => 0, 'y' => 0, 'z' => 0) );
		$this->_x = $kwargs['dest']->getX() - $kwargs['orig']->getX();
		$this->_y = $kwargs['dest']->getY() - $kwargs['orig']->getY();
		$this->_z = $kwargs['dest']->getZ() - $kwargs['orig']->getZ();
		$this->_w = $kwargs['dest']->getW() - $kwargs['orig']->getW();
		if (self::$verbose == TRUE)
			printf('Vector( x:%.2f, y:%.2f, z:%.2f, w:%.2f ) constructed' . PHP_EOL, $this->getX(), $this->getY(), $this->getZ(), $this->getW() );
		return;
	}

	public function __destruct() {
		if (self::$verbose == TRUE)
			printf('Vector( x:%.2f, y:%.2f, z:%.2f, w:%.2f ) destructed' . PHP_EOL, $this->getX(), $this->getY(), $this->getZ(), $this->getW() );
		return;
	}

	public function __toString() {
		return (sprintf('Vector( x:%.2f, y:%.2f, z:%.2f, w:%.2f )', $this->getX(), $this->getY(), $this->getZ(), $this->getW() ) );
	}

	public function magnitude() {
		return (sqrt($this->getX() * $this->getX() + $this->getY() * $this->getY() + $this->getZ() * $this->getZ() ) );
	}

	public function normalize() {
		$magnitude = $this->magnitude();
		return (new Vector( array( 'dest' => new Vertex( array( 'x' => $this->getX() / $magnitude, 'y' => $this->getY() / $magnitude, 'z' => $this->getZ() / $magnitude ) ) ) ) );		
	}

	public function add( Vector $rhs) {
		return (new Vector( array( 'dest' => new Vertex( array( 'x' => $this->getX() + $rhs->getX(), 'y' => $this->getY() + $rhs->getY(), 'z' => $this->getZ() + $rhs->getZ() ) ) ) ) );
	}

	public function sub( Vector $rhs) {
		return (new Vector( array( 'dest' => new Vertex( array( 'x' => $this->getX() - $rhs->getX(), 'y' => $this->getY() - $rhs->getY(), 'z' => $this->getZ() - $rhs->getZ() ) ) ) ) );
	}
	public function opposite() {
		return (new Vector( array( 'dest' => new Vertex( array( 'x' => -$this->getX() , 'y' => -$this->getY(), 'z' => -$this->getZ() ) ) ) ) );
	}

	public function scalarProduct( $k ) {
		return (new Vector( array( 'dest' => new Vertex( array( 'x' => $this->getX() * $k , 'y' => $this->getY() * $k , 'z' => $this->getZ() * $k ) ) ) ) );
	}

	public function dotProduct( Vector $rhs ) {
		return ($this->getX() * $rhs->getX() + $this->getY() * $rhs->getY() + $this->getZ() * $rhs->getZ() );
	}

	public function cos( Vector $rhs ) {
		return ( $this->dotProduct( $rhs ) / ( abs( $this->magnitude() * sqrt( $rhs->getX() * $rhs->getX() + $rhs->getY() * $rhs->getY() + $rhs->getZ() * $rhs->getZ() ) ) ) );
	}
	public function crossProduct( Vector $rhs ) {
		return (new Vector( array( 'dest' => new Vertex( array( 'x' => $this->getY() * $rhs->getZ() - $this->getZ() * $rhs->getY() , 'y' => $this->getZ() * $rhs->getX() - $this->getX() * $rhs->getZ() , 'z' => $this->getX() * $rhs->getY() - $this->getY() * $rhs->getX() ) ) ) ) );
	}

}

?>
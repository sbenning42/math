<?PHP

require_once 'Color.class.php';

Class Vertex {

	public static $verbose = FALSE;

	public static function doc() {
		print (file_get_contents("./Vertex.doc.txt"));
		return;
	}

	private $_x;
	private $_y;
	private $_z;
	private $_w = 1;
	private $_color;

	public function getX() { return $this->_x; }
	public function getY() { return $this->_y; }
	public function getZ() { return $this->_z; }
	public function getW() { return $this->_w; }
	public function getColor() { return $this->_color; }

	public function setX( $nb ) {
		$this->_x = $nb;
		return;
	}
	public function setY( $nb ) {
		$this->_y = $nb;
		return;
	}
	public function setZ( $nb ) {
		$this->_z = $nb;
		return;
	}
	public function setW( $nb ) {
		$this->_w = $nb;
		return;
	}
	public function setColor( Color $Color ) {
		$this->_color = $Color;
		return;
	}

	public function __construct( array $kwargs ) {
		if ( !array_key_exists('x', $kwargs) || !array_key_exists('y', $kwargs) || !array_key_exists('z', $kwargs) )
			return;
		$this->setX( $kwargs['x'] );
		$this->setY( $kwargs['y'] );
		$this->setZ( $kwargs['z'] );
		if ( array_key_exists( 'w', $kwargs ) )
			$this->setW( $kwargs['w'] );
		if ( array_key_exists( 'color', $kwargs ) )
			$this->setColor( $kwargs['color'] );
		else
			$this->setColor( new Color( array( 'red' => 255, 'green' => 255, 'blue' => 255 )));
		if (self::$verbose == TRUE)
			printf('Vertex( x: %.2f, y: %.2f, z:%.2f, w:%.2f, %s ) constructed' . PHP_EOL, $this->getX(), $this->getY(), $this->getZ(), $this->getW(), $this->getColor());
		return;
	}

	public function __destruct() {
		if (self::$verbose == TRUE)
			printf('Vertex( x: %.2f, y: %.2f, z:%.2f, w:%.2f, %s ) destructed' . PHP_EOL, $this->getX(), $this->getY(), $this->getZ(), $this->getW(), $this->getColor());
		return;
	}

	public function __toString() {
		if (self::$verbose == TRUE)
			return (sprintf('Vertex( x: %.2f, y: %.2f, z:%.2f, w:%.2f, %s )', $this->getX(), $this->getY(), $this->getZ(), $this->getW(), $this->getColor()));
		else
			return (sprintf('Vertex( x: %.2f, y: %.2f, z:%.2f, w:%.2f )', $this->getX(), $this->getY(), $this->getZ(), $this->getW()));
	}

	public function add( Vertex $instance ) {
		return (new Color( array( 'x' => $this->getX() + $instance->getX(), 'y' => $this->getY() + $instance->getY(), 'z' => $this->getZ() + $instance->getZ(), 'w' => $this->getW() + $instance->getW(), 'Color' => $this->getColor()->add( $instance->getColor() ))));
	}
	
	public function sub( Vertex $instance ) {
		return (new Color( array( 'x' => $this->getX() - $instance->getX(), 'y' => $this->getY() - $instance->getY(), 'z' => $this->getZ() - $instance->getZ(), 'w' => $this->getW() - $instance->getW(), 'Color' => $this->getColor()->sub( $instance->getColor() ))));
	}
	
	public function mult( $nb ) {
		return (new Color( array( 'x' => $this->getX() * $nb, 'y' => $this->getY() * $nb, 'z' => $this->getZ() * $nb, 'w' => $this->getW() * $nb, 'Color' => $this->getColor()->mult( $nb ))));
	}

//	public function equal( Vertex $vth ) {
//		if ( $this->getX() === $vth->getX() &&  $this->getY() === $vth->getY() && $this->getZ() === $vth->getZ() )
//			return true;
//		return false;
//	}
}

?>

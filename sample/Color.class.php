<?PHP

Class Color {

	public static $verbose = FALSE;
	public $red = 0;
	public $green = 0;
	public $blue = 0;

	public static function doc() {
		print (file_get_contents("./Color.doc.txt"));
		return;
	}

	public function __construct( array $kwargs ) {
		if ( array_key_exists( 'red', $kwargs ) )
			$this->red = $kwargs['red'] % 256;
		if ( array_key_exists( 'blue', $kwargs ) )
			$this->blue = $kwargs['blue'] % 256;
		if ( array_key_exists( 'green', $kwargs ) )
			$this->green = $kwargs['green'] % 256;
		if ( array_key_exists( 'rgb', $kwargs ) )
			{
				$this->red = ($kwargs['rgb'] >> 16) % 256;
				$this->green = ($kwargs['rgb'] >> 8) % 256;
				$this->blue = $kwargs['rgb'] % 256;
			}
		if (self::$verbose == TRUE)
			printf( 'Color( red: %3d, green: %3d, blue: %3d ) constructed.' . PHP_EOL, $this->red, $this->green, $this->blue);
		return;
	}

	public function __destruct() {
		if (self::$verbose == TRUE)
		printf( 'Color( red: %3d, green: %3d, blue: %3d ) destructed.' . PHP_EOL, $this->red, $this->green, $this->blue);
		return;
	}

	public function __toString() {
		return (sprintf( 'Color( red: %3d, green: %3d, blue: %3d )', $this->red, $this->green, $this->blue));
	}

	public function add( Color $instance ) {
		return (new Color( array( 'red' => $this->red + $instance->red, 'green' => $this->green + $instance->green, 'blue' => $this->blue + $instance->blue)));
	}
	
	public function sub( Color $instance ) {
		return (new Color( array( 'red' => $this->red - $instance->red, 'green' => $this->green - $instance->green, 'blue' => $this->blue - $instance->blue)));
	}
	
	public function mult( $nb ) {
		return (new Color( array( 'red' => $this->red * $nb, 'green' => $this->green * $nb, 'blue' => $this->blue * $nb)));
	}

	public function toPngColor( $image ) {
		$color = imagecolorallocate( $image, $this->red, $this->green, $this->blue );
		if ( $color === false )
			$color = imagecolorresolve( $image, $this->red, $this->green, $this->blue );
	return ( $color ); 
	}
	
	public function bifusion( Color $destination, $advancement ) {
		$o = $this->mult( 1 - $advancement );
		$e = $destination->mult( $advancement );
		return ( $o->add( $e ) );
	}
	
	public function trifusion(Color $A, $progA, Color $B, $progB, Color $C, $progC) {
		$a = $A->mult($progA);
		$b = $B->mult($progB);
		$c = $C->mult($progC);
		return ($a->add($b)->add($c));
	}
}
?>

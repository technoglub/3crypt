#include "include/files/files.hpp"
#include "vgp.hpp"

void VGP::cbc_encrypt_file(const std::string * const filename, const uint8_t * const key, const uint8_t * const iv,
                           const std::string * const optional_output_filename) const
{
  using namespace std;
  //Validate arguments somewhat
  if constexpr( Debug ) {
    {//+
      bool bug_exit = false;
      if( (key == nullptr) || (iv == nullptr) ) { // Diallow key or iv from being nullptr. That wouldn't make sense.
        fprintf( stderr, "ERROR: VGP::encrypt_file -- Either the key or the initialization vector was a nullptr\n"
                         "The Key: %p\n"
                         "The IV : %p\n", key, iv );
        bug_exit = true;
      }
      if( bug_exit )                              // If any bugs above encountered, die.
        exit( 1 );
    }//-
  }

  //Open the input file, and the file to write to.
  string new_filename = (*filename) + ".3f512"; // appended file extension
  if( optional_output_filename != nullptr )     // if we were given an optional output filename, make sure we open and write to that specified filename
    new_filename = (*optional_output_filename);
  cbc_t cbc{ ThreeFish<512>{ reinterpret_cast<const uint64_t*>(key) } }; // feed key
  cbc.manually_set_state( iv );                // & iv into the cbc_t object
  FILE * const input_file = fopen( filename->c_str(), "rb" );      // open the input file
  FILE * const output_file = fopen( new_filename.c_str(), "wb" ); // open the output file
  //Check if files successfully opened
  if constexpr( Debug ) {
    if( (input_file == nullptr) || (output_file == nullptr) ) {
      fprintf( stderr, "Failed to open input file or output file\n"
                       "Input file is: %p\n"
                       "Output file is: %p\n", input_file, output_file );
    }
  }
  const size_t input_file_size = get_file_size( input_file );           // see how big the file is
  static constexpr const size_t Buffer_Bytes = 64;    // we will operate on 512-bit blocks (64-byte) of the file at a time.
  uint8_t buffer[ Buffer_Bytes * 2 ];                 // Make the buffer 2 blocks wide, to accomodate for padding at the end.
  //Write the IV into the beginning of the file.
  fwrite( iv, 1, Buffer_Bytes, output_file );

  //Encrypt up to the the last block
  const size_t last_input_block_offset = (input_file_size > Buffer_Bytes) ? (input_file_size - Buffer_Bytes) : 0; // offset of the final block
  cbc.manually_set_state( iv ); // set the iv
  for( size_t in_off = 0; in_off < last_input_block_offset; in_off += Buffer_Bytes ) { // iterate over all blocks except the last
    fread( buffer, 1, Buffer_Bytes, input_file );   // get 512 bits (64 bytes) from file into buffer
    cbc.encrypt_no_padding( buffer, buffer, Buffer_Bytes );   // encrypt those 64 bytes
    fwrite( buffer, 1, Buffer_Bytes, output_file ); // write the encryptd 64 bytes to output_file
  }
  //Encrypt the last block with padding
  {//+
    fread( buffer, 1, input_file_size - last_input_block_offset, input_file );
    size_t last_block = cbc.encrypt( buffer, buffer, input_file_size - last_input_block_offset ); // encrypts the last block: minimum 1, maximum 2 blocks
    fwrite( buffer, 1, last_block, output_file ); //
  }//-
  //Cleanup
  explicit_bzero( buffer, sizeof(buffer) );
  fclose( input_file );
  fclose( output_file );
}

void VGP::cbc_decrypt_file(const std::string * const encrypted_filename, const uint8_t * const key, const uint8_t * const iv,
                           const std::string * const plaintext_filename) const
{
  using namespace std;


  //Validate arguments somewhat
  if constexpr( Debug ) {
    {//+
      bool bug_exit = false;
      if( (key == nullptr) || (iv == nullptr) ) { // Diallow key or iv from being nullptr. That wouldn't make sense.
        fprintf( stderr, "ERROR: VGP::encrypt_file -- Either the key or the initialization vector was a nullptr\n"
                         "The Key: %p\n"
                         "The IV : %p\n", key, iv );
        bug_exit = true;
      }
      if( bug_exit )                              // If any bugs above encountered, die.
        exit( 1 );
    }//-
  }
}

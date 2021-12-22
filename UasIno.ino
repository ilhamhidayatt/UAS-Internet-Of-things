// Menampilkan halaman web

#include <EtherCard.h>

#define STATIC 1  // set ke 1 untuk menonaktifkan DHCP (sesuaikan nilai myip/gwip di bawah)

#if STATIC
// alamat ip antarmuka ethernet
static byte myip[] = { 192,168,43,200 };
// gateway ip address
static byte gwip[] = { 192,168,43,160 };
#endif

// alamat mac ethernet - harus unik di jaringan Anda
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };

byte Ethernet::buffer[500]; // tcp/ip send and receive buffer

const char page[] PROGMEM =
"HTTP/1.0 503 Service Unavailable\r\n"
"Content-Type: text/html\r\n"
"Retry-After: 600\r\n"
"\r\n"
"<html>"
  "<head><title>"
    "PROJEK UAS INTERNET OF THINGS"
  "</title></head>"
  "<body>"
    "<h3>Ilham Hidayat Sidik</h3><br />"
    "<h3>NIM : V3920065</h3><br />"
    "<h3>UAS PROJEK AKHIR INTERNET OF THINGS</h3><br />"
    "<h3>Email : ilhamhidayatt10student.uns.ac.id </h3><br />"
  "</body>"
"</html>"
;

void setup(){
  Serial.begin(57600);
  Serial.println("\n[backSoon]");

  // Ubah 'SS' ke pin Slave Select Anda, jika Anda tidak menggunakan pin default
  if (ether.begin(sizeof Ethernet::buffer, mymac, SS) == 0)
    Serial.println( "Failed to access Ethernet controller");
#if STATIC
  ether.staticSetup(myip, gwip);
#else
  if (!ether.dhcpSetup())
    Serial.println("DHCP failed");
#endif

  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);
  ether.printIp("DNS: ", ether.dnsip);
}

void loop(){
  // tunggu paket TCP masuk, tapi abaikan isinya
  if (ether.packetLoop(ether.packetReceive())) {
    memcpy_P(ether.tcpOffset(), page, sizeof page);
    ether.httpServerReply(sizeof page - 1);
  }
}

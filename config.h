/**
 * @gilbellosta, 2023-04-11
 * Configuration parameters
 */


const char *SSID = "YOUR_SSID";
const char *wifi_password = "YOUR_PASSWORD";

// NTP server
const char *ntpServer = "pool.ntp.org";

// strftime() time format
const char *time_format = "%H:%M:%S";   // eg. 16:45:23
//const char *time_format = "%l:%M %p";   // eg. 4:45 PM

// Timezone strings from https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv
char *timezone = "PST8PDT,M3.2.0,M11.1.0";      char *timezone_text = "Berkeley";
// char *timezone = "MST7MDT,M3.2.0,M11.1.0";      char *timezone_text = "Denver";
// char *timezone = "CST6CDT,M3.2.0,M11.1.0";      char *timezone_text = "Chicago";
// char *timezone = "EST5EDT,M3.2.0,M11.1.0";      char *timezone_text = "New York";
// char *timezone = "GMT0BST,M3.5.0/1,M10.5.0";    char *timezone_text = "London";
// char *timezone = "CET-1CEST,M3.5.0,M10.5.0/3";  char *timezone_text = "Berlin";
// char *timezone = "JST-9";                       char *timezone_text = "Tokyo";

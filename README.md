Installation
======

Requirements
======

-liboath, oathtool http://www.nongnu.org/oath-toolkit/
-SMSTools3 http://smstools3.kekekasvi.com/
-MySQL Server


Create Table
======

CREATE TABLE  `oath_users` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  `number` varchar(45) NOT NULL,
  `server` varchar(255) NOT NULL,
  `seed` varchar(255) NOT NULL,
  `params` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;

name, contains the full name of the seed-owner
number, is the mobile number and identifys the seed
server, is the identification number for the seed
seed, holds the seed data on which the token is generated
params, which will be passed to the oathlib


Customise config.cfg
======

Warning: The ordering of the lines is important, don't modify the properties unless you know what you are doing.

Please configure all properties, as they are all required to let this work.

DBSERVER, Servername of the Database
DBUSER, Database-User which has access to the 
DBPASSWORD, Password if the specified user
DBNAME, Name of database which has 'oath_users' Table.
SMSOUTPATH, path of outgoing sms for SMSTools3

License
======

This software is licensed under the Apache License, version 2 ("ALv2"), quoted below.

Copyright 2015 Basix IT <http://www.basix.de>

Licensed under the Apache License, Version 2.0 (the "License"); you may not
use this file except in compliance with the License. You may obtain a copy of
the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
License for the specific language governing permissions and limitations under
the License.

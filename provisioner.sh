#! /bin/bash
sudo apt-get update -y
sudo apt-get install apache2 -y
sudo apt-get install debconf-utils -y
debconf-set-selections <<< "mysql-server mysql-server/root_password password root"
debconf-set-selections <<< "mysql-server mysql-server/root_password_again password root"
sudo apt-get install mysql-server -y
mysql -u root -p root -e "CREATE DATABASE dagris;
USE dagris;
SOURCE /var/www/html/dagris/_db/dagris_db.sql;"
sed -i "s/bind-address.*/bind-address = 0.0.0.0/" /etc/mysql/my.cnf
sudo service mysql restart
sudo apt-get install python-software-properties build-essential -y
sudo add-apt-repository ppa:ondrej/php5 -y
sudo apt-get install php5-common php5-dev libapache2-mod-php5 php5-cli php5-fpm -y
sudo apt-get install curl php5-curl php5-gd php5-mcrypt php5-mysql -y
sudo apt-get install php-pear -y
sudo pear channel-discover pear.drush.org 
pear install drush/drush
a2enmod rewrite
sed -i "s/AllowOverride None/AllowOverride All/g" /etc/apache2/apache2.conf
sed -i "s/error_reporting = .*/error_reporting = E_ALL/" /etc/php5/apache2/php.ini
sed -i "s/display_errors = .*/display_errors = On/" /etc/php5/apache2/php.ini
cp /var/www/html/dagris/_config/dagris_vhost /etc/apache2/sites-available/dagris.local.conf
sudo a2dissite 000-default
sudo a2ensite dagris.local
sudo service apache2 restart
sudo service apache2 reload

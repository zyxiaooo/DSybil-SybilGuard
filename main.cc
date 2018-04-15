
#include <unistd.h>

#include <QVBoxLayout>
#include <QApplication>
#include <QDebug>
#include <cstdlib>
#include <ctime>
#include "main.hh"

FriendDialog::FriendDialog(QHostAddress addr1, quint16 port1, QString origin1, QString dest1, NetSocket* udpSocket1){
    
    
    addr = addr1;
    port = port1;
    origin = origin1;
    dest = dest1;
    udpSocket = udpSocket1;
    
    instruction = new QLabel(this);
    instruction -> setText(dest + " sends you a friend request");
    acceptButton = new QPushButton(this);
    acceptButton -> setText("Accept");
    rejectButton = new QPushButton(this);
    rejectButton -> setText("Reject");

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(instruction, 0, 0, 1, 2);
    layout->addWidget(acceptButton, 1, 0);
    layout->addWidget(rejectButton, 1, 1);
    setLayout(layout);

    connect(acceptButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(rejectButton, SIGNAL(clicked()), this, SLOT(reject()));

}
void FriendDialog::accept() {
    udpSocket->friendList.append(dest);
    udpSocket->replyFriend(addr, port, origin, dest, "yes");
    
    //updateFriendList();
    delete this;
    //this->close();
    
}
void FriendDialog::reject(){
    
    //this->close();
    delete this;
}

/*RateDialog::RateDialog(QString fileInfo){
    instruction = new QLabel(this);
    instruction -> setText("Please rate the file:" + fileInfo);
    badButton = new QPushButton(this);
    badButton -> setText("Bad File");
    goodButton = new QPushButton(this);
    goodButton -> setText("Good File");

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(instruction, 0, 0, 1, 2);
    layout->addWidget(goodButton, 1, 0);
    layout->addWidget(badButton, 1, 1);
    setLayout(layout);

    connect(goodButton, SIGNAL(clicked()), this, SLOT(good()));
    connect(badButton, SIGNAL(clicked()), this, SLOT(bad()));
    qDebug() << fileInfo;

}
void RateDialog::good() {
    
    
}
void RateDialog::bad(){

    
} */   
    

ChatDialog::ChatDialog()
{
  setWindowTitle("Peerster");
  
  tabWidget = new QTabWidget();
  peerWidget = new QWidget();
  fileWidget = new QWidget();
  //messageWidget = new QWidget();
    
  QHBoxLayout *mainLayout = new QHBoxLayout();
    
  
  ////////peer part
  QHBoxLayout *peerLayout = new QHBoxLayout();
  
  QVBoxLayout *peerLayout1 = new QVBoxLayout();
  QVBoxLayout *peerLayout2 = new QVBoxLayout();
  QVBoxLayout *peerLayout3 = new QVBoxLayout();
  QVBoxLayout *peerLayout4 = new QVBoxLayout();
  
  textview = new QTextEdit(this);
  textview->setReadOnly(true);
  
  label1 = new QLabel(this);
  label1->setText("Message Box");  
  label2 = new QLabel(this);
  label2->setText("Input Box");
  
  
  inputBox = new QTextEdit(this);
  inputBox->setFocus();
  inputBox->setMaximumHeight(55);
  inputBox->installEventFilter(this);
  
  peerLayout1->addWidget(label1);
  peerLayout1->addWidget(textview);
  peerLayout1->addWidget(label2);
  peerLayout1->addWidget(inputBox);
  
  //////
  addButton = new QPushButton("Add New Neighbour");
  addFriend = new QPushButton("Add Friend");
  startChat = new QPushButton("Private Chat");
  deleteFriend = new QPushButton("Delete Friend");
  
  host = new QTextEdit(this);
  host->setMaximumHeight(30);
  host->setMaximumWidth(180);
  port = new QTextEdit(this);
  port->setMaximumHeight(30);
  port->setMaximumWidth(80);  
  
  neighbour_list = new QTextEdit(this);
  neighbour_list->setReadOnly(true);
  
  label3 = new QLabel(this);
  label3->setText("Neighbour List");
  label5 = new QLabel(this);
  label5->setText("HostName");
  label6 = new QLabel(this);
  label6->setText("Port");
  
  peerLayout2->addWidget(label3);
  peerLayout2->addWidget(neighbour_list);
  
  QVBoxLayout *layout5 = new QVBoxLayout();
  layout5->addWidget(label5);
  layout5->addWidget(host);

  QVBoxLayout *layout6 = new QVBoxLayout();
  layout6->addWidget(label6);
  layout6->addWidget(port);
  
  QHBoxLayout *layout4 = new QHBoxLayout();
  layout4->addLayout(layout5);
  layout4->addLayout(layout6);
  
  peerLayout2->addLayout(layout4);
  peerLayout2->addWidget(addButton);
  
  
  routingTBL = new QListWidget(this);
  routingTBL->setMaximumWidth(180);
  label7 = new QLabel(this);
  label7->setText("Routing Table");  

  peerLayout3->addWidget(label7);  
  peerLayout3->addWidget(routingTBL);
  
  QHBoxLayout *layout7 = new QHBoxLayout();
  layout7->addWidget(startChat);
  layout7->addWidget(addFriend);
  peerLayout3->addLayout(layout7);
  
  friend_list = new QListWidget(this);
  
  label11 = new QLabel(this);
  label11->setText("My Friends");
  
  peerLayout4->addWidget(label11);
  peerLayout4->addWidget(friend_list);
  //QHBoxLayout *layout5 = new QHBoxLayout();
  peerLayout4->addWidget(deleteFriend);

  
  peerLayout->addLayout(peerLayout1);
  peerLayout->addLayout(peerLayout2);
  peerLayout->addLayout(peerLayout3);
  peerLayout->addLayout(peerLayout4);

  //////////file part   
  QHBoxLayout *fileLayout = new QHBoxLayout();
  
  QVBoxLayout *fileLayout1 = new QVBoxLayout();
  QVBoxLayout *fileLayout2 = new QVBoxLayout();
  QVBoxLayout *fileLayout3 = new QVBoxLayout();
  
  fileSelect = new QPushButton("Select Local File");
  nameSearch = new QPushButton("Search File Name");
  viewVoter = new QPushButton("See Voters");
  upVote = new QPushButton("Good File");
  downVote = new QPushButton("Bad File");
  reputation = new QPushButton("See DSybil Reputations");
  
  label4 = new QLabel(this);
  label4->setText("Searched Files");  
  label12 = new QLabel(this);
  label12->setText("Uploaded Files");  
  label13 = new QLabel(this);
  label13->setText("Downloaded Files");  
  label9 = new QLabel(this);
  label9->setText("Enter Keyword");
  
  filenameview = new QLineEdit(this);  
  shared_file = new QListWidget(this);
  downloaded_file = new QListWidget(this);
  searched_file = new QListWidget(this);
    
  fileLayout1->addWidget(label12);
  fileLayout1->addWidget(shared_file);
  fileLayout1->addWidget(fileSelect);
  fileLayout1->addWidget(viewVoter);
  
  fileLayout2->addWidget(label4);
  fileLayout2->addWidget(searched_file);
  fileLayout2->addWidget(label9);
  fileLayout2->addWidget(filenameview);
  fileLayout2->addWidget(nameSearch);
  
  fileLayout3->addWidget(label13);
  fileLayout3->addWidget(downloaded_file);
  QHBoxLayout *layout8 = new QHBoxLayout();
  layout8->addWidget(upVote);
  layout8->addWidget(downVote);
  fileLayout3->addLayout(layout8);
  fileLayout3->addWidget(reputation);
  
  fileLayout->addLayout(fileLayout1);
  fileLayout->addLayout(fileLayout2);
  fileLayout->addLayout(fileLayout3); 
  
  //layout_m->addWidget(label8);
  //layout_m->addWidget(searchview);
  //layout_m);
    
  /////////////main part

  peerWidget-> setLayout(peerLayout);
  fileWidget -> setLayout(fileLayout);
  //tabWidget->addTab(messageWidget, "Message");
  tabWidget->addTab(peerWidget, "Peer");
  tabWidget->addTab(fileWidget, "File");
    
  mainLayout->addWidget(tabWidget);
    
  setLayout(mainLayout);
    
    
  ///////////////////////////////////////////////////  

  //connect(textline, SIGNAL(returnPressed()),
	//	this, SLOT(gotReturnPressed()));
  connect(addButton,SIGNAL(clicked()),this,SLOT(pressHandle()));
  connect(fileSelect,SIGNAL(clicked()),this,SLOT(fileHandle()));
  connect(viewVoter,SIGNAL(clicked()),this,SLOT(viewVoterHandle()));
  connect(upVote,SIGNAL(clicked()),this,SLOT(upVoteHandle()));
  connect(downVote,SIGNAL(clicked()),this,SLOT(downVoteHandle()));
  connect(reputation,SIGNAL(clicked()),this,SLOT(reputationHandle()));
  connect(deleteFriend,SIGNAL(clicked()),this,SLOT(deleteHandle()));
  connect(addFriend,SIGNAL(clicked()),this,SLOT(friendHandle()));
  connect(startChat,SIGNAL(clicked()),this,SLOT(selectHandle()));
  
  connect(nameSearch,SIGNAL(clicked()),this,SLOT(nameSearchHandle()));
  //connect(routingTBL,SIGNAL(itemDoubleClicked(QListWidgetItem *)),this,SLOT(selectHandle(QListWidgetItem*)));
  
  connect(searched_file,SIGNAL(itemDoubleClicked(QListWidgetItem *)),this,SLOT(downloadHandle(QListWidgetItem*)));
}

void ChatDialog::valid(QString temp1, QString temp2){
  QHostAddress temp3;
  bool flag;
  quint32 p = temp2.toUInt(&flag,10);
  if(flag && p <= 65536){
    port->setText(temp2);
    if(temp3.setAddress(temp1)){
      //qDebug() << "PORT IS" << p;
      
      addHost(temp3,p);
      host->clear();
      port->clear();
    }
    else
      QHostInfo::lookupHost(temp1,this,SLOT(lookedUp(QHostInfo)));
  }
}

void ChatDialog::upVoteHandle(){ // update dsybil score for each voter if good vote
  QList<QListWidgetItem* > item = downloaded_file->selectedItems();
  int index = downloaded_file->row(item[0]);
  if(item.size() == 0 || udpSocket->voted[index] == 1) return; 
  
  item[0]->setBackground(Qt::gray);
  udpSocket->voted[index] = 1;
  if(udpSocket->fileToScore[udpSocket->downloadedHashs[index]] >= OVERWHELMTHRESHOLD)
      return ;
  QVariantList voters = udpSocket->voters_searchedFile[udpSocket->downloadedHashs[index]];
  for (int i = 0;i < voters.size(); i++){
      if(udpSocket->localScore[voters[i].toString()] == 0)
          udpSocket->localScore[voters[i].toString()] = 0.2;
      else
          udpSocket->localScore[voters[i].toString()] *= 2;
      qDebug() << udpSocket->localScore[voters[i].toString()];
  }
  udpSocket->sendVoter(udpSocket->downloadedHashs[index]);
  udpSocket->pendingVoter = udpSocket->downloadedHashs[index];
}

void ChatDialog::downVoteHandle(){ // if bad votes...
  QList<QListWidgetItem* > item = downloaded_file->selectedItems();
  int index = downloaded_file->row(item[0]);
  if(item.size() == 0 || udpSocket->voted[index] == 1) return; 
  
  udpSocket->voted[index] = 1;
  
  item[0]->setBackground(Qt::gray);
  QVariantList voters = udpSocket->voters_searchedFile[udpSocket->downloadedHashs[index]];
  for (int i = 0;i < voters.size(); i++){
      udpSocket->localScore[voters[i].toString()] *= 0.5;
  }
  udpSocket->sendVoter(udpSocket->downloadedHashs[index]);
  udpSocket->pendingVoter = udpSocket->downloadedHashs[index];
}


void ChatDialog::pressHandle()
{
	// Initially, just echo the string locally.
	// Insert some networking code here...
	//qDebug() << "Pressed ";
	//textview->append(textline->toPlainText());
  QString temp1 = host->toPlainText();
  QString temp2 = port->toPlainText();
  //list->append(host->toPlainText() + ":" + port->toPlainText());
  valid(temp1,temp2);
  
}


void ChatDialog::fileHandle(){//read local file
    
  //shared_file->clear();  
    
  QFileDialog dialog(this);
  dialog.setDirectory(QDir::currentPath());
  dialog.setFileMode(QFileDialog::ExistingFiles);
  dialog.setNameFilter("All files (*.*)");
  QStringList files;
  if (dialog.exec())
	  files = dialog.selectedFiles();

  if(!QCA::isSupported("sha1"))
        qDebug() <<"SHA1 not supported!"; 

  //qDebug() << "selected file path: "<<fileNames;
  for(int i =0;i < files.size();i++){
    //file size
    QFileInfo fi(files[i]);
    if(fi.size() >= 3355443){
      qDebug() << "File too large!";
      continue;
    }
    //file name
    
    udpSocket->filenames.append(files[i]);
    
    QFile file(files[i]);
    if(!file.open(QIODevice::ReadOnly))
      qDebug() << "Unable to open";
     
    QCA::Hash shaHash("sha1");
    QByteArray meta;
    while(!file.atEnd()){
      QByteArray fillerString =  file.read(8192);

      //QCA::Hash("sha1")::hash(fillerString);
      QByteArray hashResult = shaHash.hash(fillerString).toByteArray();
      meta += hashResult;
      //fileHash.append(hashResult);
      udpSocket->hashToFilename[hashResult] = files[i];
    }
    file.close();

    //metafile
    //qDebug() << QString::fromUtf8(meta.toHex());
    QByteArray result = shaHash.hash(meta).toByteArray();
    
    
    ////////NEW
    QVariantList temp_vec;
    temp_vec.clear();
    temp_vec.append(QVariant(udpSocket->selfName));
    udpSocket->voters_localFile[result] = temp_vec;

    ////////
    
    qDebug() << QString::fromUtf8(result.toHex()); 
    udpSocket->hashToMetafile[result] = meta;
    udpSocket->fileids.append(result);
    
    QListWidgetItem *temp = new QListWidgetItem;
    temp->setText(files[i]);
    shared_file->addItem(temp);
  }
  
  
}

void ChatDialog::nameSearchHandle(){//search file through network
  QString input = filenameview->text();
  filenameview->clear();
  udpSocket->budget = 2;
  udpSocket->curKeyword = input;
  QMap<QString,QPair<QHostAddress,quint16>>::const_iterator i =  udpSocket->neighbourList.constBegin();
  udpSocket->fileNumber = 0;
  while(i != udpSocket->neighbourList.constEnd()){
    udpSocket->requestSearch(i.value().first,i.value().second,udpSocket->selfName, input, 2);
    i++;
  }

  //NEW clear the random route target 
  udpSocket->random_route_targets.clear();
  udpSocket->voters_searchedFile.clear();
  udpSocket->fileToScore.clear();
  ////
}

void ChatDialog::downloadHandle(QListWidgetItem* item){//download file from network
  QString filename = item->text().left(item->text().lastIndexOf(':'));
  int index = searched_file->row(item);
  
  QByteArray fileid = udpSocket->wantedFileIDs[index];
  if(udpSocket->downloadedHashs.contains(fileid))
      return ;
  
  udpSocket->voted.append(0);
  udpSocket->downloadedFiles.append(filename);
  udpSocket->downloadedHashs.append(fileid);
  
  QString dest = udpSocket->fileSourceTable[fileid];
  QHostAddress addr = udpSocket->routingTable[dest].first;
  quint16 port = udpSocket->routingTable[dest].second;
  
  udpSocket->wantedHash = fileid;
  udpSocket->curName = filename;
  
  QFile file(filename);
  file.remove();

  udpSocket->requestBlock(addr, port, udpSocket->selfName, dest, fileid);

}

void ChatDialog::friendHandle(){//add friend 
  QList<QListWidgetItem* > item = routingTBL->selectedItems();
  if(item.size() == 0) return; 
  
  udpSocket->addFriend(item[0]->text());
    
}

void ChatDialog::deleteHandle(){//delete friend
  QList<QListWidgetItem* > item = friend_list->selectedItems();
  if(item.size() == 0) return; 
  
  udpSocket->deleteFriend(item[0]->text());
  updateFriendList();
}

void ChatDialog::reputationHandle(){//see each voter's reputation
    QWidget *window = new QWidget;
  
    QHBoxLayout *layout = new QHBoxLayout();
    QVBoxLayout *layout1 = new QVBoxLayout();
    QVBoxLayout *layout2 = new QVBoxLayout();
    QLabel* title1 = new QLabel();
    QLabel* title2 = new QLabel(); 
    
    title1->setText("Identities:");
    layout1->addWidget(title1);
    
    title2->setText("Score:");
    layout2->addWidget(title2);
     
	for(QMap<QString,float>::const_iterator i = udpSocket->localScore.begin();i != udpSocket->localScore.end(); ++i){

        QLabel* temp1 = new QLabel();
        temp1->setText(i.key());
        layout1->addWidget(temp1);
      
        QLabel* temp2 = new QLabel();
        temp2->setText(QString::number(i.value()));
        layout2->addWidget(temp2);
	}
    layout->addLayout(layout1);
    layout->addLayout(layout2);

    window->setLayout(layout);
    window->show();  
}

void ChatDialog::viewVoterHandle(){//see voters
  QList<QListWidgetItem* > item = shared_file->selectedItems();
  if(item.size() == 0) return; 
  
  //udpSocket->deleteFriend(item[0]->text());
  QWidget *window = new QWidget;
  
  QVBoxLayout *layout = new QVBoxLayout();

  
  QString filename = item[0]->text();
  QByteArray hash;
  for (int i =0;i<udpSocket->filenames.size(); i++){
      if(udpSocket->filenames[i] == filename){
          hash = udpSocket->fileids[i];
          break;
      }
  }
  QLabel* temp = new QLabel();
  temp->setText("Voters:");
  layout->addWidget(temp);
  for(int i=0; i<udpSocket->voters_localFile[hash].size();i++){
      QLabel* voter = new QLabel();
      voter->setText(udpSocket->voters_localFile[hash][i].toString());
      layout->addWidget(voter);
  }
  
  window->setLayout(layout);
  window->show();  
}

void ChatDialog::selectHandle(/*QListWidgetItem* item*/){
  //qDebug() << item->text();
  
  QList<QListWidgetItem* > item = routingTBL->selectedItems();
  if(item.size() == 0) return;
  
  QWidget *window = new QWidget;

  QVBoxLayout *layout = new QVBoxLayout();
  QLabel* title = new QLabel();
  
  select = new QLabel(this);
  select->setText(item[0]->text());

  QString t = "Private Talk to ";
  title->setText(t);
  layout->addWidget(title);
  layout->addWidget(select);
  pri = new QTextEdit;
  pri->setFocus();
  pri->installEventFilter(this);


  layout->addWidget(pri);
  window->setLayout(layout);
  window->show();

}
void ChatDialog::lookedUp(const QHostInfo &h){
  if(h.error() != QHostInfo::NoError){
    qDebug() << "Lookup failed:" << h.errorString();
    return;
  }
  foreach(const QHostAddress &address, h.addresses()){
   
    qDebug() << "Found address: "<<address.toString();
    addHost(address,port->toPlainText().toUInt());
    
    host->clear();
    port->clear();
    break;
  }

}

void ChatDialog::updateFileList(){//show file list and score after search
  QMap<QByteArray, QVariantList>::const_iterator iter = udpSocket->voters_searchedFile.constBegin();
    
    while(iter != udpSocket->voters_searchedFile.constEnd()){
        udpSocket->fileToScore[iter.key()] = 0.0;
        for (int k=0;k<iter.value().size();k++){
          if(iter.value()[k].toString() == udpSocket->selfName)
              continue;
         if(udpSocket->isRunningSBG == true)udpSocket->fileToScore[iter.key()] += udpSocket->localScore[iter.value()[k].toString()] * 1.0 + udpSocket->random_route_targets[iter.value()[k].toString()]*0.5;
         else udpSocket->fileToScore[iter.key()] += udpSocket->localScore[iter.value()[k].toString()] * 1.0;
        }
        //threshold
        /*if(fileToScore[iter.key()] > 1.0)
          overwhelm.append(iter.key());
        else
          nonoverwhelm.append(iter.key());*/

        iter++;
    }

  searched_file->clear();

  for (int i = 0;i<udpSocket->wantedFileIDs.size();i++){
    QListWidgetItem *temp = new QListWidgetItem;
    temp->setText(udpSocket->wantedFileList[udpSocket->wantedFileIDs[i]] + ':' + QVariant(udpSocket->fileToScore[udpSocket->wantedFileIDs[i]]).toString());
    searched_file->addItem(temp);
    
    if(udpSocket->fileToScore[udpSocket->wantedFileIDs[i]] >= 1.0)
        temp->setBackground(Qt::green);
    else
        temp->setBackground(Qt::red);
      
  }

}




void ChatDialog::updateFriendList(){//update friend list when add friend
  friend_list->clear();

  for (int i =0;i<udpSocket->friendList.size(); i++){
    
    QListWidgetItem *temp = new QListWidgetItem;
    temp->setText(udpSocket->friendList[i]);
    
    qDebug() << udpSocket->friendList[i];
    friend_list->addItem(temp);
  }
}

void ChatDialog::showDialog(QHostAddress addr, quint16 port, QString origin, QString dest){
    friendDialog = new FriendDialog(addr,port,origin,dest,udpSocket);
    friendDialog->show();
    
    //friendDialog->close();
    
}
    
    
void ChatDialog::setSocket(NetSocket* sock){
  udpSocket = sock;
}

void ChatDialog::setTextView(QString s){
  textview->append(s);
}

void ChatDialog::addHost(QHostAddress addr, quint16 port){
  QString key = addr.toString() + ":" +  QString::number(port);
  //udpSocket->neighbourList[key] = qMakePair(addr,port);
  udpSocket->neighbourList.insert(key,qMakePair(addr,port));
  
  //list->append(addr.toString() + ":" + QString::number(port));
  //qDebug() << "ADD PORT" << port;
  neighbour_list->append(key);
}

bool ChatDialog::eventFilter(QObject *obj, QEvent *event){
  if(event->type() == QEvent::KeyPress){
    QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
    if(keyEvent->key() == Qt::Key_Return){
     
      QString origin = udpSocket->selfName;
      if(obj == inputBox){
        QString msg = inputBox->toPlainText();
        if(msg == "")
          return true;
        
        quint32 seq = udpSocket->rumorIndex[origin];

        udpSocket->sendRumor(udpSocket->selfIP,udpSocket->curPort, msg, origin, seq, false);
        
        inputBox->clear();
        return true;
      }
      else if(obj == pri){
        QString dest = select->text();
        if(udpSocket->routingTable.contains(dest)){
          
          udpSocket->sendPrivate(udpSocket->routingTable.value(dest).first, udpSocket->routingTable.value(dest).second, origin, dest, pri->toPlainText(),10);
        }
        pri->clear();
        return true;
      }
      else if(false){
        



      }

    }
  }
  return QObject::eventFilter(obj,event);
  
}


void NetSocket::setDialog(ChatDialog * dia){
    //connect(sock,SIGNAL(readyRead()),sock,SLOT(getMsg(NetSocket *)));
    dialog = dia;
}

NetSocket::NetSocket()
{
	// Pick a range of four UDP ports to try to allocate by default,
	// computed based on my Unix user ID.
	// This makes it trivial for up to four Peerster instances per user
	// to find each other on the same host,
	// barring UDP port conflicts with other applications
	// (which are quite possible).
	// We use the range from 32768 to 49151 for this purpose.
	myPortMin = 32768 + (getuid() % 4096)*4;
	myPortMax = myPortMin + 3;
}

bool NetSocket::bind()
{
	// Try to bind to each of the range myPortMin..myPortMax in turn.
  //QHostAddress addr = QHostAddress::LocalHost;
  
  foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
    if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost)){
      selfIP =  address;
      qDebug() << "my IP is" << selfIP;
      break;
    }
}


  for (int p = myPortMin; p <= myPortMax; p++) {
		if (QUdpSocket::bind(p)) {
			qDebug() << "bound to UDP port " << p;
      curPort = p;

      //init neighbour
      if(p-1 >= myPortMin){
        //QString temp = getOrigin(selfIP,p-1);
        //neighbourList[temp] = qMakePair(selfIP,quint16(p-1));
        dialog->addHost(selfIP,p-1);
      }
      if(p+1 <= myPortMax){
        //QString temp = getOrigin(selfIP,p+1);
        //neighbourList[temp] = qMakePair(selfIP,quint16(p+1));
        dialog->addHost(selfIP,p+1);
      }
      
      connect(this,SIGNAL(readyRead()),this,SLOT(readPendingDatagrams()));
      QTimer *timer1 = new QTimer(this);
      QTimer *timer2 = new QTimer(this);
      QTimer *timer3 = new QTimer(this);
      QTimer *timer4 = new QTimer(this);
      QTimer *timer5 = new QTimer(this);
      
      SBGResultTimer = new QTimer(this);
      SBGFollowerTimer = new QTimer(this);
      
      SBGResultTimer = new QTimer(this);
	  SBGFollowerTimer = new QTimer(this);
	  SBGResultTimer -> setSingleShot(true);
	  SBGFollowerTimer -> setSingleShot(true);

	  connect(SBGResultTimer, SIGNAL(timeout()),this, SLOT(SBGCalculateRes()));
	  connect(SBGFollowerTimer, SIGNAL(timeout()),this, SLOT(SBGClearStatus()));
      
      
      
      connect(timer1,SIGNAL(timeout()),this,SLOT(timeoutRumor()));
      connect(timer2,SIGNAL(timeout()),this,SLOT(timeoutStatus()));
      connect(timer3,SIGNAL(timeout()),this,SLOT(timeoutRoute()));
      connect(timer4,SIGNAL(timeout()),this,SLOT(timeoutBlock()));
      connect(timer5,SIGNAL(timeout()),this,SLOT(timeoutSearch()));
      timer1->start(2000);
      timer2->start(10000);
      timer3->start(60000);
      timer4->start(1000);
      timer5->start(3000);
			return true;
		}
	}

	qDebug() << "Oops, no ports in my default range " << myPortMin
		<< "-" << myPortMax << " available";
	return false;
}

void NetSocket::sendVoter(QHostAddress addr, quint16 port, QString origin, QString dest, QByteArray fileid, quint32 limit){
  qDebug() << "sendVoterto" << addr;//send voter to the file searching ndoe
  QMap<QString,QVariant> map;
  map["Origin"] = QVariant(origin);
  map["HopLimit"] = QVariant(limit);
  map["Dest"] = QVariant(dest);
  map["VotedFile"] = QVariant(fileid);
  QByteArray arr;
  QDataStream out(&arr, QIODevice::WriteOnly);
  out << map;

  this->writeDatagram(arr,addr,port);

}

void NetSocket::sendVoter(QByteArray fileid){
    QString dest = fileSourceTable[fileid];
    
    sendVoter(routingTable[dest].first, routingTable[dest].second , selfName, dest, fileid);
}


void NetSocket::sendRoute(QHostAddress addr, quint16 port,QString origin,quint32 seq, bool isFW){
  //qDebug() << "sendRouterto" << addr;
  QMap<QString,QVariant> map;
  map["Origin"] = QVariant(origin);
  map["SeqNo"] = QVariant(seq);
  if(isFW){
    map["LastIP"] = QVariant(latestIP);
    map["LastPort"] = QVariant(latestPort);
  }
  QByteArray arr;
  QDataStream out(&arr, QIODevice::WriteOnly);
  out << map;

  this->writeDatagram(arr,addr,port);

}

void NetSocket::requestSearch(QHostAddress addr, quint16 port, QString origin, QString search, quint32 budget){
  //QMap<QString,QPair<QHostAddress,quint16>>::const_iterator i =  neighbourList.constBegin();
  QMap<QString,QVariant> map;
  //while(i != neighbourList.constEnd()){
  map["Origin"] = QVariant(origin);
  map["Search"] = QVariant(search);
  map["Budget"] = QVariant(budget);
  QByteArray arr;
  QDataStream out(&arr, QIODevice::WriteOnly);
  out << map;

  this->writeDatagram(arr,addr,port);
    
    //i ++;
  //}

}
////////NEW
void NetSocket::replySearch(QHostAddress addr, quint16 port, QString origin, QString dest, QString search, QVariantList filenames, QVariantList ids, QVariantList corresponding_voters, quint32 limit){
  QMap<QString,QVariant> map;
  map["Origin"] = QVariant(origin);
  map["HopLimit"] = QVariant(limit);
  map["Dest"] = QVariant(dest);
  map["SearchReply"] = QVariant(search);
  map["MatchNames"] = QVariant(filenames);
  map["MatchIDs"] = QVariant(ids);
  map["Voters"] = QVariant(corresponding_voters);
  QByteArray arr;
  QDataStream out(&arr, QIODevice::WriteOnly);
  out << map;

  this->writeDatagram(arr,addr,port);
}


void NetSocket::requestBlock(QHostAddress addr, quint16 port, QString origin, QString dest, QByteArray hash, quint32 limit){
  
  QMap<QString,QVariant> map;
  map["Origin"] = QVariant(origin);
  map["HopLimit"] = QVariant(limit);
  map["Dest"] = QVariant(dest);
  map["BlockRequest"] = QVariant(hash);
  QByteArray arr;
  QDataStream out(&arr, QIODevice::WriteOnly);
  out << map;

  this->writeDatagram(arr,addr,port);

}

void NetSocket::replyBlock(QHostAddress addr, quint16 port, QString origin, QString dest, QByteArray hash, QByteArray data, quint32 limit){
  qDebug() << "send reply to " << dest;
  QMap<QString,QVariant> map;
  map["Origin"] = QVariant(origin);
  map["HopLimit"] = QVariant(limit);
  map["Dest"] = QVariant(dest);
  map["BlockReply"] = QVariant(hash);
  map["Data"] = QVariant(data);
  QByteArray arr;
  QDataStream out(&arr, QIODevice::WriteOnly);
  out << map;

  this->writeDatagram(arr,addr,port);

}

void NetSocket::sendRumor(QHostAddress addr,quint16 port,QString msg, QString origin,  quint32 seq, bool isFW){
  QMap<QString,QVariant> map;
  map["ChatText"] = QVariant(msg);
  //QString dest = getOrigin(addr,port);
  map["Origin"] = QVariant(origin);
  map["SeqNo"] = QVariant(seq);
  if(isFW){
    map["LastIP"] = QVariant(latestIP);
    map["LastPort"] = QVariant(latestPort);
  }

  QByteArray arr;
  QDataStream out(&arr, QIODevice::WriteOnly);
  out << map;

  this->writeDatagram(arr,addr,port);
 
}

void NetSocket::sendPrivate(QHostAddress addr, quint16 port, QString origin, QString dest, QString msg, quint32 limit){
  qDebug() << "sendPrivate" << msg << "to" << addr << port;

  QMap<QString,QVariant> map;
  map["ChatText"] = QVariant(msg);
  map["Origin"] = QVariant(origin);
  map["HopLimit"] = QVariant(limit);
  map["Dest"] = QVariant(dest);

  QByteArray arr;
  QDataStream out(&arr, QIODevice::WriteOnly);
  out << map;

  this->writeDatagram(arr,addr,port);

}

void NetSocket::sendStatus(QHostAddress addr,quint16 port){
  //qDebug() << "send status to" << port; 
  //QMap<QString,QMap<QString, quint32>> map;
  QVariantMap map;
  //QMap<QString,quint32> temp;
  QVariantMap temp;
  QMap<QString,quint32>::const_iterator i =  rumorIndex.constBegin();
  //QVariantMap::const_iterator i =  rumorIndex.constBegin();
  while( i != rumorIndex.constEnd()){
    temp[i.key()] = i.value();
    i++;
  }
  map["Want"] = temp;
  //qDebug() << "sending statue "<< map;
  QByteArray arr;
  QDataStream out(&arr, QIODevice::WriteOnly);
  out << map;

  this->writeDatagram(arr,addr,port);

}

void NetSocket::replyFriend(QHostAddress addr, quint16 port, QString origin, QString dest, QString reply, quint32 limit){
    dialog->updateFriendList();
    QVariantMap myData2;		//p2p message
	myData2["Dest"] = QVariant(dest);
	//myData2["ChatText"] = QVariant(privateDialog.textline->toPlainText());
	myData2["Origin"] = QVariant(origin);
	myData2["HopLimit"] = QVariant(limit);//reply friend request
            
	myData2["FriendReply"] = QVariant(reply);
           
	QByteArray data2;
	QDataStream serialize(&data2, QIODevice::WriteOnly);

	serialize << myData2;
	
	this->writeDatagram(data2, addr, port);
    //emit pre_send_Message(data2, pointPeer.first, pointPeer.second);
	qDebug() << "send *Friend reply* message" + dest;
}

void NetSocket::requestFriend(QHostAddress addr, quint16 port, QString origin, QString dest, quint32 limit){//send request for add friends
    QVariantMap myData2;		//p2p message
	myData2["Dest"] = QVariant(dest);
	//myData2["ChatText"] = QVariant(privateDialog.textline->toPlainText());
	myData2["Origin"] = QVariant(origin);
	myData2["HopLimit"] = QVariant(limit);
	myData2["FriendRequest"] = QVariant(QString(""));
	QByteArray data2;
	QDataStream serialize(&data2, QIODevice::WriteOnly);

	serialize << myData2;
	//emit pre_send_Message(data2, pointPeer.first, pointPeer.second);
    this->writeDatagram(data2, addr , port);
    
}

//////sbg///////////

void NetSocket::deleteFriend(QString destination){//delete a friend
    for(int i = 0; i < friendList.size(); ++i){
		if(friendList[i] == destination){
            friendList.remove(i);
            break;
        }
    
	}
    
    QPair<QHostAddress, quint16> pointPeer = routingTable[destination];
    replyFriend(pointPeer.first, pointPeer.second, selfName, destination, "delete");

}


void NetSocket::addFriend(QString destination){
	bool flag = false;
	QPair<QHostAddress, quint16> pointPeer = routingTable[destination];
	for(int i = 0; i < friendList.size(); ++i){
		if(friendList[i] == destination)flag = true;
	}
    
	if(flag == false){
        targetFriend = destination;
		requestFriend(pointPeer.first,pointPeer.second,selfName,destination);
	    qDebug() << "Send friend request to" << destination;
	}
}

void NetSocket::launchSBG(){//verifier running sybilguard 
	if(isRunningSBG == true){
		qDebug() << "SybilGuard is running, please wait";
		return;
	}
	if(friendList.size() == 0){
		qDebug() << "No friend, sybilguard stopped";
    dialog->updateFileList();
		return;
	}
   processing = new QWidget;

  QHBoxLayout *layout = new QHBoxLayout();
  QLabel* temp = new QLabel();
  temp->setText("Running Sybil Guard. Please Wait!");
  layout->addWidget(temp);


  processing->setLayout(layout);
  processing->show(); 
	isRunningSBG = true;
	SBGResultTimer -> start(3000);
	notifySBG();
	runSBGLauncher();
}

void NetSocket::notifySBG(){//notify all the voter to start sybilguard
	//get all voter;
     
    QMap<QString,float>::const_iterator _iter = random_route_targets.constBegin();
      while(_iter != random_route_targets.constEnd()){
        //launch random route
        QVector<int> tmp;
		SBGResult[_iter.key()] = tmp;
       
        QString destination = _iter.key();
		QVariantMap myData2;		//p2p message
		myData2["Dest"] = QVariant(destination);
		myData2["Origin"] = QVariant(selfName);
		myData2["HopLimit"] = QVariant(40);
		myData2["LaunchSBG"] = "";
		QByteArray data2;
		QDataStream serialize(&data2, QIODevice::WriteOnly);
		serialize << myData2;
		QPair<QHostAddress, quint16> pointPeer = routingTable[destination];
	    this->writeDatagram(data2, pointPeer.first, pointPeer.second);
       
       
        _iter++;
      }

	/*for(int i = 0; i < voterList.size(); ++i){
		QVector<int> tmp;
		SBGResult[voterList[i]] = tmp;
	}*/

	/*for(int i = 0; i < voterList.size(); ++i){
		QString destination = voterList[i];
		QVariantMap myData2;		//p2p message
		myData2["Dest"] = QVariant(destination);
		myData2["Origin"] = QVariant(selfName);
		myData2["HopLimit"] = QVariant(40);
		myData2["LaunchSBG"] = "";
		QByteArray data2;
		QDataStream serialize(&data2, QIODevice::WriteOnly);
		serialize << myData2;
		QPair<QHostAddress, quint16> pointPeer = routingTable[destination];
	    this->writeDatagram(data2, pointPeer.first, pointPeer.second);
        //emit pre_send_Message(data2, pointPeer.first, pointPeer.second);
	}*/
}

void NetSocket::runSBGLauncher(){//verifier send sybilguard random route packets
	for(int i = 0; i < PATHNUM; ++i){

		QString destination = friendList[i % friendList.size()];
		qDebug() << "---- send launcher to ----" << destination;
           
		QVariantMap myData2;		//p2p message
		myData2["Dest"] = QVariant(destination);
		myData2["Origin"] = QVariant(selfName);
		myData2["HopLimit"] = QVariant(40);
		myData2["SBGLauncher"] = QVariant(selfName);
		myData2["SBGPathLength"] = QVariant(PATHLENGTH);
		myData2["SBGPathNO"] = QVariant(i);
		QByteArray data2;
		QDataStream serialize(&data2, QIODevice::WriteOnly);
		serialize << myData2;
		QPair<QHostAddress, quint16> pointPeer = routingTable[destination];
	    this->writeDatagram(data2, pointPeer.first, pointPeer.second);
        //emit pre_send_Message(data2, pointPeer.first, pointPeer.second);
	}
}

void NetSocket::runSBGFollower(QString launcher){//voter send sybilguard random route packets
	SBGFollowWith.insert(launcher);
    if(friendList.size() == 0)return;
	for(int i = 0; i < PATHNUM; ++i){
		QString destination = friendList[i % friendList.size()];
		qDebug() << "---- send follower to ----" << destination;

		QVariantMap myData2;		//p2p message
		myData2["Dest"] = QVariant(destination);
		myData2["Origin"] = QVariant(selfName);
		myData2["HopLimit"] = QVariant(40);
		myData2["SBGFollower"] = QVariant(selfName);
		myData2["SBGLauncher"] = launcher;
		myData2["SBGPathLength"] = QVariant(PATHLENGTH);
		myData2["SBGPathNO"] = QVariant(i);
		QByteArray data2;
		QDataStream serialize(&data2, QIODevice::WriteOnly);
		serialize << myData2;
		QPair<QHostAddress, quint16> pointPeer = routingTable[destination];
	    this->writeDatagram(data2, pointPeer.first, pointPeer.second);
        //emit pre_send_Message(data2, pointPeer.first, pointPeer.second);
	}
}

void NetSocket::SBGCalculateRes(){//calculate sybilguard results after finishing sybilguard process
    processing->close();
    delete processing;
    
    QWidget *window = new QWidget;
  
    QHBoxLayout *layout = new QHBoxLayout();
    QVBoxLayout *layout1 = new QVBoxLayout();
    QVBoxLayout *layout2 = new QVBoxLayout();
    QLabel* title1 = new QLabel();
    QLabel* title2 = new QLabel(); 
    
    title1->setText("Targets:");
    layout1->addWidget(title1);
    
    title2->setText("Relevance:");
    layout2->addWidget(title2);
    
    //dialog->showSBGResult(SBGResult);
    
	for(QMap<QString, QVector<int>>::const_iterator i = SBGResult.begin();i != SBGResult.end(); ++i){
        random_route_targets[i.key()] = i.value().size()*1.0/PATHNUM;
        
        QLabel* temp1 = new QLabel();
        temp1->setText(i.key());
        layout1->addWidget(temp1);
      
        QLabel* temp2 = new QLabel();
        temp2->setText(QString::number(random_route_targets[i.key()]));
        layout2->addWidget(temp2);
	}
    layout->addLayout(layout1);
    layout->addLayout(layout2);

    window->setLayout(layout);
    window->show(); 
    
    
    //compute score



    dialog->updateFileList();
      //select file by their scores or overwhelming
    /*if(overwhelm.size() > 0){
        int target = rand()%overwhelm.size(); 

    }
    else{
        int target = rand()%nonoverwhelm.size();

    }*/
    SBGResult.clear();
	isRunningSBG = false;
}

void NetSocket::SBGClearStatus(){//clear last sybilguard status
	SBGLauncherCache.clear();
	SBGFollowerCache.clear();
	SBGFollowWith.clear();
}

//////////////////////////////

void NetSocket::timeoutBlock(){
  if(!wantedHash.isEmpty()){
    qDebug() << "timeout to send block";
    QString dest = fileSourceTable[wantedHash];
    requestBlock(routingTable[dest].first, routingTable[dest].second, selfName, dest , wantedHash); 
  }
}

void NetSocket::timeoutVoter(){
  if(!pendingVoter.isEmpty()){
    
    QString dest = fileSourceTable[pendingVoter];
    sendVoter(routingTable[dest].first, routingTable[dest].second, selfName, dest , pendingVoter);
  }
}



void NetSocket::timeoutSearch(){
  if(budget != 0){
    budget *= 2;
    QMap<QString,QPair<QHostAddress,quint16>>::const_iterator i =  neighbourList.constBegin();
    while(i != neighbourList.constEnd()){
      requestSearch(i.value().first,i.value().second, selfName, curKeyword, budget);
      i++;
    }
    
  }
}

void NetSocket::timeoutRoute(){
  QMap<QString,QPair<QHostAddress,quint16>>::const_iterator i =  neighbourList.constBegin();
  
  while(i != neighbourList.constEnd()){
    
    sendRoute(i.value().first, i.value().second, selfName, rumorIndex[selfName], false);
    i ++;
  }
  //QHostAddress addr = i.value().first;
  //quint16 port = i.value().second;
  
  //sendRoute(addr,port,selfName,rumorIndex[selfName], false);
  rumorIndex[selfName]++;
  rumorList[selfName].append("");

}

void NetSocket::timeoutRumor(){
  QMap<QString,QPair<QString,quint32>>::const_iterator i =  pendingList.constBegin();
  
  while( i != pendingList.constEnd()){

    QString dest = i.key();
    QPair<QString,quint32> temp = i.value();
    QString origin = temp.first;
    quint32 seq = temp.second;

    QString msg = rumorList[origin][seq-1];
    if(!neighbourList.contains(dest))
      return ;
    QHostAddress addr = neighbourList[dest].first;
    quint16 port = neighbourList[dest].second;

    QMap<QString,QVariant> map;
    map["ChatText"] = QVariant(msg);
  
    map["Origin"] = QVariant(origin);
    map["SeqNo"] = QVariant(seq);

    QByteArray arr;
    QDataStream out(&arr, QIODevice::WriteOnly);
    out << map;

    this->writeDatagram(arr,addr,port);
    i++;
  }

}

void NetSocket::timeoutStatus(){
  //qDebug() << "timeout to send status";
  //qDebug() << routingTable;
  //qsrand(123);
  
  int len = neighbourList.size();
  //qDebug() << "has" << neighbourList << "neighbour";
  int index = rand()%len;
  QMap<QString,QPair<QHostAddress,quint16>>::const_iterator i =  neighbourList.constBegin();
  for(int j =0 ;j <index;j++)
    i ++;
  QHostAddress addr = i.value().first;
  quint16 port = i.value().second;
  
  sendStatus(addr,port);

}

void NetSocket::privateMsgProcess(QMap<QString,QVariant> &primitive, QString origin){
          
    /*if(primitive.value("Dest").toString() != selfName){
        if(noforward == false){
          QString dest = primitive.value("Dest").toString();
          sendPrivate(routingTable[dest].first, 
                      routingTable[dest].second, 
                      origin, 
                      dest, 
                      primitive.value("ChatText").toString(), 
                      primitive.value("HopLimit").toUInt()-1);
        }
        
        return ;
    }*/
    
    QString tmp = "[PRIVATE] from " + origin + ':';
    dialog->setTextView(tmp);
    dialog->setTextView("  " + primitive.value("ChatText").toString());
}

void NetSocket::blockRequestProcess(QMap<QString,QVariant> &primitive, QHostAddress sender, quint16 senderPort, QString origin){
    
    qDebug() << "blockrequest received";
    QByteArray temp = primitive.value("BlockRequest").toByteArray();
    /*if(primitive.value("Dest").toString() != selfName){
        if(noforward == false){
          QString dest = primitive.value("Dest").toString();
          requestBlock(routingTable[dest].first, 
                       routingTable[dest].second, 
                       origin, 
                       dest, 
                       temp, 
                       primitive.value("HopLimit").toUInt()-1);
        }
        
        return ;
    }*/
    
    
    if(hashToMetafile.contains(temp)){
      qDebug() << "find filemeta";
      replyBlock(sender, senderPort, selfName, origin, temp, hashToMetafile[temp], 10);
    }
    else if(hashToFilename.contains(temp)){
      QFile file(hashToFilename[temp]);
      //char block[8192];
      if(!file.open(QIODevice::ReadOnly))
        qDebug() << "Unable to open";

      QCA::Hash shaHash("sha1");

      while(!file.atEnd()){
        //int block_size = file.read(block,8192);
        //QByteArray fillerString = QByteArray(block,block_size);
        QByteArray fillerString = file.read(8192);

        QByteArray hashResult = shaHash.hash(fillerString).toByteArray();
        if(hashResult == temp){
          qDebug() << "find file block";
          replyBlock(sender, senderPort, selfName, origin, temp, fillerString);
          break;
        }
      }
      file.close();                   
    }
    
}
void NetSocket::blockReplyProcess(QMap<QString,QVariant> &primitive, QHostAddress sender, quint16 senderPort, QString origin){
    if(!primitive.contains("Data"))
      return;
    qDebug() << "Blockreply received";
    
    QByteArray data = primitive.value("Data").toByteArray();
    QByteArray hash = primitive.value("BlockReply").toByteArray();
    
    /*if(primitive.value("Dest").toString() != selfName){
        if(noforward == false){
          QString dest = primitive.value("Dest").toString();
          replyBlock(routingTable[dest].first, 
                     routingTable[dest].second, 
                     origin, 
                     dest, 
                     hash, 
                     data,
                     primitive.value("HopLimit").toUInt()-1);
        }
        
        return ;
    }*/
    
    if(wantedHash == hash){
             
      if(wantedIndex == -1){
        wantedIndex = 0;
               
        wantedFileHash = data;
        //qDebug() << "receive header";
        //qDebug() << wantedFileHash.size();
      }
      else{
        if(!QDir(selfName).exists())QDir().mkdir(selfName);
        QFile file(selfName + '/' + curName);
        file.open(QIODevice::Append);
        file.write(data);
        file.close();
        wantedIndex += 1;
        if(wantedIndex == wantedFileHash.size()/20){
          wantedIndex = -1;
          wantedFileHash.clear();

          QListWidgetItem *temp = new QListWidgetItem;
          temp->setText(curName);
          dialog->downloaded_file->addItem(temp);
          
          wantedHash.clear();
          downloadedFiles.append(curName);
          qDebug() << "File Received";
        }


      }
      if(wantedIndex != -1){
        wantedHash.clear();
        for(int k = 0;k < 20; k ++)
          wantedHash += wantedFileHash[k+wantedIndex*20];
                
        requestBlock(sender, senderPort, selfName, origin, wantedHash);
      }
    }
    
}
void NetSocket::searchReplyProcess(QMap<QString,QVariant> &primitive, /*QHostAddress sender, quint16 senderPort,*/ QString origin){
    if(!primitive.contains("MatchNames") || !primitive.contains("MatchIDs") || !primitive.contains("Voters"))
      return ;
    QString replyString = primitive.value("SearchReply").toString();
    QVariantList names = qvariant_cast<QVariantList>(primitive["MatchNames"]);
    QVariantList ids = qvariant_cast<QVariantList>(primitive["MatchIDs"]);
    //////NEW add those file voters to launch random route
    QVariantList voters = qvariant_cast<QVariantList>(primitive["Voters"]);
    
    /*if(primitive.value("Dest").toString() != selfName){
        if(noforward == false){
          QString dest = primitive.value("Dest").toString();
          replySearch(routingTable[dest].first, 
                      routingTable[dest].second, 
                      origin, 
                      dest, 
                      replyString, 
                      names, 
                      ids, 
                      voters,
                      primitive.value("HopLimit").toUInt()-1);
        }
        
        return ;
    }*/
    
    
    if(fileNumber > 20 || budget >= 16){
      budget = 0;
      fileNumber = 0;
      //////NEW stop receiving new file and compute file score

      
      launchSBG();
      
  
      

    }
    if(replyString == curKeyword && fileNumber < 10){
      fileNumber += 1;
      for (int k = 0;k < voters.size(); k++){
        QVariantList voter_per_file = qvariant_cast<QVariantList>(voters[k]);
        for (int h = 0; h < voter_per_file.size();h++){
          if(voter_per_file[h].toString() == selfName)
              continue;
          random_route_targets[voter_per_file[h].toString()] = 0.0;
            
        }
        voters_searchedFile[ids[k].toByteArray()] = voter_per_file;
      }

      ////////

      if(names.size() != ids.size())
        return ;
      for (int k = 0;k < names.size(); k++){
        QString name = names[k].toString();
        QByteArray id = ids[k].toByteArray();
        
        if(!wantedFileList.contains(id))
            wantedFileIDs.append(id);
        wantedFileList[id] = name;
        
        fileSourceTable[id] = origin;
      }

      
    }
}
void NetSocket::fileVotingProcess(QMap<QString,QVariant> &primitive, QHostAddress sender, quint16 senderPort, QString origin){

    QByteArray fileid = primitive.value("VotedFile").toByteArray();
    /*if(primitive.value("Dest").toString() != selfName){
        if(noforward == false){
          QString dest = primitive.value("Dest").toString();
          sendVoter(routingTable[dest].first, 
                    routingTable[dest].second, 
                    origin, 
                    dest, 
                    fileid, 
                    primitive.value("HopLimit").toUInt()-1);
        }
        
        return ;
    }*/
    //receive reply
    if(pendingVoter == fileid){
      pendingVoter.clear();
    }
    else{
      QVariant voter = QVariant(origin);
      if(!voters_localFile[fileid].contains(voter)){
        voters_localFile[fileid].append(voter);
        
      }
      //reply, works as ack, "origin" not important
      sendVoter(sender, senderPort, selfName, origin, fileid);
    }    
}

void NetSocket::friendRequestProcess(QHostAddress sender, quint16 senderPort, QString origin ){
    
    /*if(primitive.value("Dest").toString() != selfName){
        if(noforward == false){
          QString dest = primitive.value("Dest").toString();
          requestFriend(routingTable[dest].first, 
                    routingTable[dest].second, 
                    origin, 
                    dest, 
                    primitive.value("HopLimit").toUInt()-1);
        }
        
        return ;
    }*/

	qDebug() << "Receive friend request from" << origin;	
    dialog->showDialog(sender,senderPort,selfName,origin);
           
}

void NetSocket::friendReplyProcess(QMap<QString,QVariant> &primitive, QString origin ){
    
    /*if(primitive.value("Dest").toString() != selfName){
        if(noforward == false){
          QString dest = primitive.value("Dest").toString();
          replyFriend(routingTable[dest].first, 
                    routingTable[dest].second, 
                    origin, 
                    dest, 
                    primitive["FriendReply"].toString(), 
                    primitive["HopLimit"].toUInt()-1);
        }
        
        return ;
    }*/
    qDebug() << "Receive friend Reply from" << origin;
    //qDebug() << targetFriend;
	if(primitive["FriendReply"].toString() == "yes" && origin == targetFriend){
        //qDebug() << "ddddddd";
		friendList.append(origin);
        //qDebug() << friendList.size();
        dialog->updateFriendList();
                
		if(friendList.size() > 1)randomRoute = qrand() % (friendList.size() - 1) + 1;
		else randomRoute = 0;
	}
    else if(primitive["FriendReply"].toString() == "delete"){
        for(int i = 0; i < friendList.size(); ++i){
            if(friendList[i] == origin){
                friendList.remove(i);
                break;
            }
        }
        dialog->updateFriendList();
    }
	return;
}


void NetSocket::startup(){
  QMap<QString,QPair<QHostAddress,quint16>>::const_iterator iter =  neighbourList.constBegin();
  
  const QString candidates("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
  const int len = 3;
 
  QString randomString;
  for(int i=0;i<len;i++){
    randomString.append(candidates.at(std::rand() % candidates.length()));
  }

  selfName =  randomString + selfIP.toString() + ":" + QString::number(curPort);
  //selfName = QUuid(selfIP.toString()  + QString::number(curPort)).toString();
  //qDebug() << "my name is " << selfName;

  routingTable[selfName] = qMakePair(selfIP,curPort);
  rumorIndex[selfName] = 2;
  QVector<QString> vec;
  vec.append("");
  rumorList[selfName] = vec;
  
  wantedHash = "";
  wantedIndex = -1;
  fileNumber = 0;

  while(iter != neighbourList.constEnd()){
    
    sendRoute(iter.value().first,iter.value().second,selfName,1, false);
    iter++;
  }

}
void NetSocket::readPendingDatagrams(){ 
  while(this->hasPendingDatagrams()){
    QByteArray datagram;
    datagram.resize(this->pendingDatagramSize());
    QHostAddress sender;
    quint16 senderPort;
    this->readDatagram(datagram.data(),datagram.size(),&sender,&senderPort);
   
    QMap<QString,QVariant> primitive;
    QDataStream in(&datagram,QIODevice::ReadOnly);
    in >> primitive;
    //receiving status
    if(primitive.contains("Want") && noforward == false ){
        //qDebug() << "status msg" << neighbourList.size();
        //remove pending if any
        QString key1 = sender.toString() + ":" + QString::number(senderPort);
        if(pendingList.contains(key1)){
          qDebug() << "REMOVED";  
          pendingList.remove(key1);
          //qDebug() << pendingList;
        }
        QVariantMap content = qvariant_cast<QVariantMap>(primitive["Want"]);
        //has more rumors 
       
        QMap<QString,quint32>::const_iterator i = rumorIndex.constBegin();
        while(i != rumorIndex.constEnd()){
          if(!content.contains(i.key())){
            if(rumorList[i.key()][0] == "")
              sendRoute(sender,senderPort, i.key(), 1 ,false);
            else{
              sendRumor(sender,senderPort, rumorList[i.key()][0], i.key(), 1, false);
              QString temp = sender.toString() + ":" + QString::number(senderPort);
              quint32 temp2 = 1;
              pendingList[temp] = qMakePair(i.key(),temp2);
            }
            
            return ;
          }
          else if(rumorIndex[i.key()] > content[i.key()].toUInt()){
            if(rumorList[i.key()][content[i.key()].toInt()-1] == "")
              sendRoute(sender,senderPort, i.key(), content[i.key()].toInt(), false);
            else{
              sendRumor(sender,senderPort, rumorList[i.key()][content[i.key()].toInt()-1], i.key(), content[i.key()].toInt(), false);
              QString temp = sender.toString() + ":" + QString::number(senderPort);
              pendingList[temp] = qMakePair(i.key(),content[i.key()].toUInt());
              //pendingList.insert(qMakePair(origin,seq));
            }
            
            return ;
          }
          i++;
        }
        //has less rumors
        QVariantMap::const_iterator j = content.constBegin();
        while(j != content.constEnd()){
          if(!rumorIndex.contains(j.key()) || rumorIndex[j.key()] < content[j.key()].toUInt()){
        
            sendStatus(sender,senderPort);
      
            return ;
          }
          j++;
        }
        if(rand()%2 == 0 && latestRumor != ""){
          //choose
          int len = neighbourList.size();
          int index = rand()%len;

          QMap<QString,QPair<QHostAddress,quint16>>::const_iterator i =  neighbourList.constBegin();
          for(int j =0 ;j <index;j++)
            i ++;
          QHostAddress addr = i.value().first;
          quint16 port = i.value().second;
          sendRumor(addr,port,latestRumor, latestOrigin, latestSeq,true);
          QString temp = addr.toString() + ":" + QString::number(port);
          pendingList[temp] = qMakePair(latestOrigin,latestSeq);

        }

    }
    // rumor both route and none and private
    else if (primitive.contains("Origin")){
      //bool flag3 = false;
      if(primitive.contains("LastIP") && primitive.contains("LastPort")){
        bool f1,f2;
        quint32 temp1 = primitive.value("LastIP").toUInt(&f1);
        quint16 temp2 = primitive.value("LastPort").toUInt(&f2);
        if((temp1 != selfIP.toIPv4Address() || temp2 != curPort) && f1 == true && f2 == true && !neighbourList.contains(QHostAddress(temp1).toString()+":"+QString::number(temp2)))
          dialog->addHost(QHostAddress(temp1),temp2);
      }
      
      QString origin = primitive.value("Origin").toString();

      if(origin != selfName && !neighbourList.contains(sender.toString()+":"+QString::number(senderPort))){
        
        dialog->addHost(sender,senderPort);
      }
      
      ///////////////////////////////////////////////
      if(!routingTable.contains(origin)){
        routingTable[origin] = qMakePair(sender,senderPort);
        QListWidgetItem *temp = new QListWidgetItem;
        temp->setText(origin);
        dialog->routingTBL->addItem(temp);

        /////NEW
        localScore[origin] = 0.0;
        ///////

      }

      if(primitive.contains("Search") ){
        if(!primitive.contains("Budget") )
          return ;
        QString words = primitive.value("Search").toString();
        QStringList keywords = words.split(' ', QString::SkipEmptyParts);
        int remain = primitive.value("Budget").toInt();
       
        if(remain > 0){
          //search local
          QVariantList matchedNames;
          QVariantList matchedIds;

          /////NEW  2d array
          QVariantList corresponding_voters;
          ///////


          for(int i =0 ;i< filenames.size();i++){
            for(int j = 0; j < keywords.size(); j++){
              if(filenames[i].contains(keywords[j])){
                QStringList temp = filenames[i].split('/');
                QString truncated = temp.last();
                matchedNames.append(QVariant(truncated));
                matchedIds.append(QVariant(fileids[i]));
                //////NEW
                corresponding_voters.append(QVariant(voters_localFile[fileids[i]]));
                ////////
                break;
              }
            }
          }
          if(!matchedIds.isEmpty()){
            replySearch(sender, senderPort, selfName, origin, words, matchedNames, matchedIds,corresponding_voters);
          }

          //reboardcast
          remain --;
          int nums = neighbourList.size();
          int avg = remain/nums;
          if(avg > 0){
            QMap<QString,QPair<QHostAddress,quint16>>::const_iterator i =  neighbourList.constBegin();
            while(i != neighbourList.constEnd()){
              requestSearch(i.value().first,i.value().second,selfName, words, avg);
              i++;
            }

          }

        }


      }
      

      if(primitive.contains("HopLimit") && primitive.value("HopLimit").toUInt() > 0){
        if(!primitive.contains("Dest") || !routingTable.contains(primitive.value("Dest").toString()))
          return ;
        //qDebug() << "PRIVATE/FILE REQUEST RECEIVED";
        if(primitive["Dest"].toString() == selfName){  
          if(primitive.contains("ChatText")){
            privateMsgProcess(primitive, origin);
            
          }
          else if(primitive.contains("BlockRequest")){
            blockRequestProcess(primitive, sender, senderPort, origin);
            

          }
          else if(primitive.contains("BlockReply")){
            blockReplyProcess(primitive, sender, senderPort, origin);
            
          }
          else if(primitive.contains("SearchReply")){
            searchReplyProcess(primitive,/* sender, senderPort, */origin);  
            
          }
          /////NEW
          else if(primitive.contains("VotedFile")){
            fileVotingProcess(primitive, sender, senderPort, origin);
            
          }
          //////
          
          else if(primitive.contains("FriendReply")){
            friendReplyProcess(primitive,origin);
			
		  }

		  else if(primitive.contains("FriendRequest")){
            friendRequestProcess(sender, senderPort, origin );
		  }
        
            if(primitive.contains("LaunchSBG")){
                qDebug() << "receive LaunchSBG message";
			
                runSBGFollower(origin);
                SBGFollowerTimer -> start(3000);
                return;
            }

            if(primitive.contains("SBGFeedback")){//verifier and follower intersect, send sybilguard feedback
                qDebug() << "receive SBGFeedback message";
			
                if(isRunningSBG == false)return;
                if(SBGResult.size() == 0 && !SBGResult.contains(primitive["SBGFollower"].toString()))return;
                QVector<int> t = SBGResult[primitive["SBGFollower"].toString()];
                //if(std::find(t.begin(), t.end(), primitive["SBGPathNO"].toInt()) == t.end()){
                if(!t.contains(primitive["SBGPathNO"].toInt())){
                    SBGResult[primitive["SBGFollower"].toString()].push_back(primitive["SBGPathNO"].toInt());
                    SBGResultTimer -> start(3000);
                }

                return;
            }

            if(primitive.contains("SBGFollower")){//receive followers random route packets
                //if(primitive["SBGFollower"] == name)return;
                //update cache
                qDebug() << "receive SBGFollower message";
                //qDebug() << primitive;
                SBGFollowerTimer -> start(3000);
                if(SBGFollowerCache.contains(primitive["SBGLauncher"].toString())){
                    QVector<QPair<QString, int>> t = SBGFollowerCache[primitive["SBGLauncher"].toString()];
                    int i = 0;
                    for(i = 0; i < t.size(); ++i){
                        if(t[i].first == primitive["SBGFollower"].toString() && t[i].second == primitive["SBGPathNO"].toInt())break;
                    }
                    if(i == t.size()){
                        SBGFollowerCache[primitive["SBGLauncher"].toString()].push_back(QPair<QString, int>(primitive["SBGFollower"].toString(), primitive["SBGPathNO"].toInt()));
                    }
                }

                else {
                    QVector<QPair<QString, int> > t;
                    t.push_back(QPair<QString, int>(primitive["SBGFollower"].toString(), primitive["SBGPathNO"].toInt()));
                    SBGFollowerCache[primitive["SBGLauncher"].toString()] = t;
                }

                if(SBGResult.contains(primitive["SBGFollower"].toString())){
                    int i = 0, no = primitive["SBGPathNO"].toInt();
                    for(i = 0; i < SBGResult[primitive["SBGFollower"].toString()].size(); ++i){
                        if(SBGResult[primitive["SBGFollower"].toString()][i] == no)break;
                    }
                    if(i == SBGResult[primitive["SBGFollower"].toString()].size())SBGResult[primitive["SBGFollower"].toString()].push_back(no);
                }
    
                else if(SBGLauncherCache.contains(primitive["SBGLauncher"].toString())){
                    //send feedback
                    QVector<int> t = SBGLauncherCache[primitive["SBGLauncher"].toString()];
                    //if(std::find(t.begin(), t.end(), primitive["SBGPathNO"].toInt())!=t.end()){
                    if(!t.contains(primitive["SBGPathNO"].toInt())){
                        QString destination = primitive["SBGLauncher"].toString();
                        qDebug() << "---- transmit follower to ----" << destination;
             
                        QVariantMap myData2;		//p2p message
                        myData2["Dest"] = QVariant(destination);
                        myData2["Origin"] = QVariant(selfName);
                        myData2["HopLimit"] = QVariant(400);
                        myData2["SBGFeedback"] = "";
                        myData2["SBGFollower"] = primitive["SBGFollower"];
                        myData2["SBGLauncher"] = primitive["SBGLauncher"];
                        myData2["SBGPathNO"] = primitive["SBGPathNO"];
                        QByteArray data2;
                        QDataStream serialize(&data2, QIODevice::WriteOnly);
                        serialize << myData2;
                        QPair<QHostAddress, quint16> pointPeer = routingTable[destination];
                        this->writeDatagram(data2, pointPeer.first, pointPeer.second);
                        //emit pre_send_Message(data2, pointPeer.first, pointPeer.second);
                    }

                }

                else {
                    //forward
                    if(primitive["SBGPathLength"].toInt() == 0)return;
                    int friendOrigin = 0; 
                    for(friendOrigin = 0; friendOrigin < friendList.size(); ++friendOrigin){
                        if(friendList[friendOrigin] == primitive["Origin"].toString())break;
                    }
                    if(friendOrigin == friendList.size()){
                        qDebug() << "not a friend? Something wrong happened";
                        return;
                    }
                    QString destination = friendList[(friendOrigin + randomRoute) % friendList.size()];
                    QVariantMap myData2;		
                    myData2["Dest"] = QVariant(destination);
                    myData2["Origin"] = QVariant(selfName);
                    myData2["HopLimit"] = QVariant(400);
                    myData2["SBGLauncher"] = primitive["SBGLauncher"];
                    myData2["SBGFollower"] = primitive["SBGFollower"];
                    myData2["SBGPathLength"] = QVariant(primitive["SBGPathLength"].toInt() - 1);
                    myData2["SBGPathNo"] = primitive["SBGPathNo"];
                    QByteArray data2;
                    QDataStream serialize(&data2, QIODevice::WriteOnly);
                    serialize << myData2;
                    QPair<QHostAddress, quint16> pointPeer = routingTable[destination];
                    this->writeDatagram(data2, pointPeer.first, pointPeer.second);
                    //emit pre_send_Message(data2, pointPeer.first, pointPeer.second);

                }
                return;
            }

            if(primitive.contains("SBGLauncher")){//receive verifiers random route packets
                //if(primitive["SBGLauncher"].toString() == name)return;
                qDebug() << "receive SBGLauncher message";
                qDebug() << primitive;
                //update cache
                SBGFollowerTimer -> start(3000);
                if(SBGLauncherCache.contains(primitive["SBGLauncher"].toString())){
                    QVector<int> t = SBGLauncherCache[primitive["SBGLauncher"].toString()];
                    if(!t.contains(primitive["SBGPathNO"].toInt()))return;
                    else SBGLauncherCache[primitive["SBGLauncher"].toString()].push_back(primitive["SBGPathNO"].toInt());
                }
                else {
                    QVector<int> tmp;
                    tmp.push_back(primitive["SBGPathNO"].toInt());
                    SBGLauncherCache[primitive["SBGLauncher"].toString()] = tmp;
                }

                if(SBGFollowWith.contains(primitive["SBGLauncher"].toString()) || SBGFollowerCache.contains(primitive["SBGLauncher"].toString())){
                    //send feedback
                    if(SBGFollowWith.contains(primitive["SBGLauncher"].toString())){
                        QString destination = primitive["SBGLauncher"].toString();
                        QVariantMap myData2;		//p2p message
                        myData2["Dest"] = QVariant(destination);
                        myData2["Origin"] = QVariant(selfName);
                        myData2["HopLimit"] = QVariant(400);
                        myData2["SBGFeedback"] = "";
                        myData2["SBGFollower"] = QVariant(selfName);
                        myData2["SBGLauncher"] = primitive["SBGLauncher"];
                        myData2["SBGPathNO"] = primitive["SBGPathNO"];
                        QByteArray data2;
                        QDataStream serialize(&data2, QIODevice::WriteOnly);
                        serialize << myData2;
                        QPair<QHostAddress, quint16> pointPeer = routingTable[destination];
                        this->writeDatagram(data2, pointPeer.first, pointPeer.second);
                        //emit pre_send_Message(data2, pointPeer.first, pointPeer.second);
                    }

                    else {
                        //check sbgcache
                        int no = primitive["SBGPathNO"].toInt();
                        for(int i = 0; i < SBGFollowerCache[primitive["SBGLauncher"].toString()].size(); ++i){
                            if(no == SBGFollowerCache[primitive["SBGLauncher"].toString()][i].second){
                                QString destination = primitive["SBGLauncher"].toString();
                                QVariantMap myData2;		//p2p message
                                myData2["Dest"] = QVariant(destination);
                                myData2["Origin"] = QVariant(selfName);
                                myData2["HopLimit"] = QVariant(400);
                                myData2["SBGFeedback"] = "";
                                myData2["SBGFollower"] = QVariant(SBGFollowerCache[primitive["SBGLauncher"].toString()][i].first);
                                myData2["SBGLauncher"] = primitive["SBGLauncher"];
                                myData2["SBGPathNO"] = primitive["SBGPathNO"];
                                QByteArray data2;
                                QDataStream serialize(&data2, QIODevice::WriteOnly);
                                serialize << myData2;
                                QPair<QHostAddress, quint16> pointPeer = routingTable[destination];
                                this->writeDatagram(data2, pointPeer.first, pointPeer.second);
                                //emit pre_send_Message(data2, pointPeer.first, pointPeer.second);
                            }
                        }
    
                    }
					
                }

                //forward
                if(primitive["SBGPathLength"].toInt() == 0)return;//if path reach the max length


                int friendOrigin = 0; 
                for(friendOrigin = 0; friendOrigin < friendList.size(); ++friendOrigin){
                    if(friendList[friendOrigin] == primitive["Origin"].toString())break;
                }
                if(friendOrigin == friendList.size()){
                    qDebug() << "not a friend? Something wrong happened";
                    return;
                }
                QString destination = friendList[(friendOrigin + randomRoute) % friendList.size()];
                qDebug() << "---- transmit launcher to ----" << destination;
                QVariantMap myData2;		
                myData2["Dest"] = QVariant(destination);
                myData2["Origin"] = QVariant(selfName);
                myData2["HopLimit"] = QVariant(400);
                myData2["SBGLauncher"] = primitive["SBGLauncher"];
                myData2["SBGPathLength"] = QVariant(primitive["SBGPathLength"].toInt() - 1);
                myData2["SBGPathNo"] = primitive["SBGPathNo"];
                QByteArray data2;
                QDataStream serialize(&data2, QIODevice::WriteOnly);
                serialize << myData2;
                QPair<QHostAddress, quint16> pointPeer = routingTable[destination];
                this->writeDatagram(data2, pointPeer.first, pointPeer.second);
                //emit pre_send_Message(data2, pointPeer.first, pointPeer.second);
				
                return;
            }
                     
        }
        else {
			if(!routingTable.contains(primitive["Dest"].toString())){
				qDebug() << "no address found, something wrong happened";
				return;
			}
			else {
				QPair<QHostAddress, quint16> tmpDest = routingTable[primitive["Dest"].toString()];
				primitive["HopLimit"] = primitive["HopLimit"].toInt() - 1;
				QByteArray data2;
				QDataStream serialize(&data2, QIODevice::WriteOnly);
				serialize << primitive;
				this->writeDatagram(data2, tmpDest.first, tmpDest.second);
			}
		}
            
      }
      
      //////////////////////////////////////////////
      if(!primitive.contains("SeqNo"))
        return;
      bool ok;
      quint32 seq = primitive.value("SeqNo").toInt(&ok);
      if(!ok)
        return;

      QString msg;
      if(primitive.contains("ChatText"))
        msg = primitive.value("ChatText").toString();
      else
        msg = "";
      bool flag = false;
      if(!rumorIndex.contains(origin)){
        if(seq == 1){
          QVector<QString> vec;
          vec.append(msg);
          rumorList[origin] = vec; 
          rumorIndex[origin] = 2;
          if(msg != ""){
            dialog->setTextView(msg);
            
          }
          flag = true;
        }
      } 
      else if(rumorIndex[origin] == seq){
        routingTable[origin] = qMakePair(sender,senderPort);
        rumorList[origin].append(msg);
        rumorIndex[origin] += 1;
        if(msg != ""){
          dialog->setTextView(msg);
          
        }
        flag = true;
      }
      else if(rumorIndex[origin] == seq + 1){
        //qDebug() << "MEET AGAIN";
        if(!primitive.contains("LastIP") && !primitive.contains("LastPort"))
          routingTable[origin] = qMakePair(sender,senderPort);

      }
      
      //dialog->setTextView(temp);
      
      if(origin != selfName) 
        sendStatus(sender,senderPort);
      

      if(flag){
        
        latestRumor = msg;
        latestOrigin = origin;
        latestIP = sender.toIPv4Address();
        latestPort = senderPort;
        latestSeq = seq;
        int len = neighbourList.size();
        int index = rand()%len;

        QMap<QString,QPair<QHostAddress,quint16>>::const_iterator i =  neighbourList.constBegin();
        for(int j =0 ;j <index;j++)
            i ++;
        QHostAddress addr = i.value().first;
        quint16 port = i.value().second;
        if(primitive.contains("ChatText") && noforward == false){
          sendRumor(addr,port,latestRumor, latestOrigin, latestSeq, true);
          QString temp = addr.toString() + ":" + QString::number(port);
          pendingList[temp] = qMakePair(latestOrigin,latestSeq);
        }
        if(!primitive.contains("ChatText")){
          QMap<QString,QPair<QHostAddress,quint16>>::const_iterator iter =  neighbourList.constBegin();
          while(iter != neighbourList.constEnd()){
            sendRoute(iter.value().first,iter.value().second, origin,seq , true);
            iter++;
          }
        }
        
      }
    }
        
  }
}

int main(int argc, char **argv)
{
  QCA::Initializer qcainit;
  // Initialize Qt toolkit
	QApplication app(argc,argv);

	// Create an initial chat dialog window
	ChatDialog dialog;
  //dialog.setFocus(textline);
	dialog.show();

	// Create a UDP network socket
	NetSocket sock;
	dialog.setSocket(&sock);
  sock.setDialog(&dialog);
  if(!sock.bind())
    exit(1);
  
  sock.noforward = false;
  std::srand(std::time(0)); 
  QStringList templist =  app.arguments();
  for(int i = 1; i < templist.size();i++){

    if(templist[1] == "-noforward"){
      sock.noforward = true;

    }
    if(templist[i].contains(':')){
      QStringList temp = templist[i].split(':');
      dialog.valid(temp[0],temp[1]);
    }
  }

  //startup send route
  //
  sock.startup();


	// Enter the Qt main loop; everything else is event driven
  return app.exec();
}


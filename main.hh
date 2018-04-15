#ifndef PEERSTER_MAIN_HH
#define PEERSTER_MAIN_HH

#include <QDialog>
#include <QTextEdit>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QUdpSocket>
#include <QDir>
#include <QEvent>
#include <QKeyEvent>
#include <QMap>
#include <QDataStream>
#include <QVariant>
#include <QByteArray>
#include <QString>
#include <QStringList>
#include <QIODevice>
#include <QHostInfo>
#include <QVector>
#include <QListWidget>
#include <QHash>
#include <QPair>
#include <QTimer>
#include <QListWidgetItem>
#include <QNetworkInterface>
#include <QtCrypto/QtCrypto>
#include <QFileDialog>
#include <QFileInfo>
#include <QFile>
#include <QList>
#include <stdlib.h>
#include <QTabWidget>
#include <QWidget>


class NetSocket;

class FriendDialog: public QDialog
{
    Q_OBJECT
public:
    FriendDialog();
    FriendDialog(QHostAddress addr1, quint16 port1, QString origin1, QString dest1, NetSocket* udpSocket1);
    QLabel *instruction;
    QPushButton *acceptButton;
    QPushButton *rejectButton;
public slots:
    void accept();
    void reject();

private:
    QHostAddress addr;
    quint16 port;
    QString origin;
    QString dest;
    NetSocket* udpSocket;

};

/*class RateDialog: public QDialog
{
    Q_OBJECT
public:
    RateDialog();
    RateDialog(QString fileInfo);
    QLabel *instruction;
    QPushButton *goodButton;
    QPushButton *badButton;
public slots:
    void good();
    void bad();

};*/


class ChatDialog : public QDialog
{
	Q_OBJECT

public:
  ChatDialog();
  
  
  
  void setTextView(QString s);
  void setSocket(NetSocket *sock);
  void addHost(QHostAddress addr,quint16 port);
  void valid(QString temp1,QString temp2);

  void showDialog(QHostAddress addr, quint16 port, QString origin, QString dest);
  
  void updateFileList();
  void updateFriendList();
  //void updateSearchedFriendList();
  //void updateDownloadedFileList();
  QListWidget *routingTBL, *shared_file, *downloaded_file, *searched_file, *friend_list;
  
public slots:
  void pressHandle();
  void selectHandle();
  void upVoteHandle();
  void downVoteHandle();
  void reputationHandle();
  void viewVoterHandle();
  
  void downloadHandle(QListWidgetItem *item);
  
  void fileHandle();
  void friendHandle();
  void deleteHandle();
  void nameSearchHandle();
  void lookedUp(const QHostInfo &host);
  //void setSocket(NetSocket *sock);
  
protected:

  bool eventFilter(QObject *obj, QEvent *event);
  NetSocket *udpSocket;
  
private:
  //main page
  
  QTabWidget *tabWidget;
  QWidget *peerWidget;
  QWidget *fileWidget;
  QWidget *messageWidget;
  FriendDialog *friendDialog;
  
  float OVERWHELMTHRESHOLD = 1.0;
  
  
  QTextEdit *textview;
  QLineEdit *filenameview,*destview;

  QTextEdit *inputBox,*pri;
  QLabel *label1,*label2,*label3,*label4,*label5,*label6,*label7,*label8,*label9,*label10,*label11, *label12, *label13;

  QTextEdit *neighbour_list;
  QTextEdit *host;
  QTextEdit *port;
  QLabel *select;

  QPushButton *addButton,*fileSelect,*addFriend, *startChat, *deleteFriend,*nameSearch, *viewVoter, *upVote, *downVote, *reputation;
};






class NetSocket : public QUdpSocket
{
	Q_OBJECT

public:
	NetSocket();
	// Bind this socket to a Peerster-specific default port.
  //void initSocket();
  void setDialog(ChatDialog *dia);
  bool bind();
  quint16 curPort;
  QHostAddress selfIP;
  QString selfName;
  void sendRumor(QHostAddress addr, quint16 port, QString msg, QString origin, quint32 seq, bool isFW);
  void sendStatus(QHostAddress addr,quint16 port);
  
  
  void requestBlock(QHostAddress addr, quint16 port, QString origin, QString dest, QByteArray hash, quint32 limit=40);
  void replyBlock(QHostAddress addr, quint16 port, QString origin, QString dest, QByteArray hash, QByteArray data, quint32 limit=40);

  void requestSearch(QHostAddress addr, quint16 port, QString origin, QString search, quint32 budget);
  void replySearch(QHostAddress addr, quint16 port, QString origin, QString dest, QString search, QVariantList filenames, QVariantList ids, QVariantList corresponding_voters, quint32 limit=40);

  void replyFriend(QHostAddress addr, quint16 port, QString origin, QString dest, QString reply, quint32 limit=40);
  void requestFriend(QHostAddress addr, quint16 port, QString origin, QString dest, quint32 limit=40);
  
  /////NEW
  //add voter to the file voter list
  void sendVoter(QHostAddress addr, quint16 port, QString origin, QString dest, QByteArray fileid, quint32 limit=40);
  void sendVoter(QByteArray fileid);
  //same with above void replyVoter(QHostAddress addr, quint16 port, QString origin, QString dest, QByteArray fileids);
  //////
  

  //route process functions
  void privateMsgProcess(QMap<QString,QVariant> &primitive, QString origin);
  void blockRequestProcess(QMap<QString,QVariant> &primitive, QHostAddress sender, quint16 senderPort, QString origin);
  void blockReplyProcess(QMap<QString,QVariant> &primitive, QHostAddress sender, quint16 senderPort, QString origin);
  void searchReplyProcess(QMap<QString,QVariant> &primitive, /*QHostAddress sender, quint16 senderPort,*/ QString origin);
  void fileVotingProcess(QMap<QString,QVariant> &primitive, QHostAddress sender, quint16 senderPort, QString origin);
  void friendRequestProcess( QHostAddress sender, quint16 senderPort, QString origin );
  void friendReplyProcess(QMap<QString,QVariant> &primitive, QString origin );
  
  

  void sendRoute(QHostAddress addr, quint16 port, QString origin, quint32 seq, bool isFW);
  void sendPrivate(QHostAddress addr, quint16 port, QString origin, QString dest, QString msg, quint32 limit=40);
  QMap<QString,quint32> rumorIndex;
  void startup();
  //QVariantMap rumorIndex;
  QMap<QString,QPair<QHostAddress,quint16>> neighbourList;
  QHash<QString,QPair<QHostAddress,quint16>> routingTable;

  //wanted filename map to fileid
  QMap<QByteArray, QString> wantedFileList;
  QVector<QByteArray> wantedFileIDs;

  QVector<QString> filenames;
  QVector<QByteArray> fileids;  
  
  QVector<int> voted;
  QVector<QString> downloadedFiles;
  QVector<QByteArray> downloadedHashs;
  
  //hash maps to its dest
  QMap<QByteArray,QString> fileSourceTable;
  
  //hash maps to its file name
  QMap<QByteArray,QString> hashToFilename;

  //hash maps to 20*N block
  QMap<QByteArray,QByteArray> hashToMetafile;

  ////NEW
  //////////////////////////
  //////////sg///////////
  QVector<QString> friendList;
  QMap<QString, QVector<int>> SBGLauncherCache; // launcher: no.
  QMap<QString, QVector<QPair<QString, int>>> SBGFollowerCache; // launcher: follower, No.
  QMap<QString, QVector<int>> SBGResult;
  
  
  void addFriend(QString destination);
  void deleteFriend(QString destination);
  void notifySBG();
  void runSBGLauncher();
  void runSBGFollower(QString launcher);
  
  void launchSBG();
    
  QSet<QString> SBGFollowWith;
  
  QTimer * SBGResultTimer;
  QTimer * SBGFollowerTimer;
    
  int randomRoute;
  int PATHNUM = 5;
  int PATHLENGTH = 1;
  
  bool isRunningSBG = false;
    
  //////////////////  
  //////////////////  

  //origin and its relative score
  QMap<QString,float> localScore;

  //local uploaded file hash and its voters received from other parties
  QMap<QByteArray, QVariantList> voters_localFile;

  //voters for searched file hash
  QMap<QByteArray, QVariantList> voters_searchedFile;

  QByteArray pendingVoter;
  
  //random route targets for this round
  QMap<QString, float> random_route_targets;

  //file and its computed score
  QMap<QByteArray, float> fileToScore;
  
  ///////


  //current wanted hash
  QByteArray wantedHash;
  int budget;
  QString curKeyword;
  QString curName;
  int fileNumber;
  bool noforward;


public slots:
  void readPendingDatagrams();
  void timeoutRumor();
  void timeoutStatus();
  void timeoutRoute();
  void timeoutBlock();
  void timeoutSearch();

  
  void SBGCalculateRes();
  void SBGClearStatus();
  
  ////NEW
  void timeoutVoter();
  //////

private:
  ChatDialog* dialog;
  //QUdpSocket* udpSocket;
  //QHash<QString,QPair<QHostAddress,quint16>> routingTable;
  //sender -> (origin, seq)
  QMap<QString,QPair<QString,quint32>> pendingList;
  //QSet<QPair<QString,quint32>> pendingList;
  
  quint32 latestSeq;
  QString latestRumor;
  QString latestOrigin;
  quint32 latestIP;
  quint16 latestPort;
  QWidget *processing;
  QString targetFriend;
  QByteArray wantedFileHash;
  //QByteArray wantedHash;
  int wantedIndex;
 
  //QHostAddress selfIP;
	quint16 myPortMin, myPortMax;
  //Origin -> List[msg1,msg2]
  QMap<QString,QVector<QString>> rumorList;
};

#endif // PEERSTER_MAIN_HH

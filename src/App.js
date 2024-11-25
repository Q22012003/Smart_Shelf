import React from 'react';
import Web from './web';

function App() {
  const styles = {
    appContainer: {
      display: 'flex',
      flexDirection: 'column',
      alignItems: 'center',
      minHeight: '10vh',
      paddingTop: '20px',
      /*backgroundColor: '#f0f0f0',*/
      fontFamily: 'Arial, sans-serif',
    },
    title: {
      fontSize: '2em',
      fontWeight: 'bold',
      marginBottom: '20px',
      textAlign: 'center',
    },
    infoContainer: {
      backgroundColor: '#bfbcbb',
      alignSelf: 'flex-start',
      paddingLeft: '20px',
      marginBottom: '20px',
      fontSize: '1em',
      lineHeight: '1.5em',
      paddingRight: '20px',
      marginLeft: '30px',
      borderRadius: '10px',
    },
    logo: {
      width: '200px', // Adjust width as needed
      height: '100px', // Maintain aspect ratio
    },
  };

  return (
    <div style={styles.appContainer}>
      <div></div>
      <h1 style={styles.title}>DACN: Hệ thống kệ hàng thông minh </h1> {/* Fixed missing closing tag */}
      <img src="https://upload.wikimedia.org/wikipedia/vi/1/1b/T%C4%90T_logo.png" alt="Your image description" style={styles.logo} />
      <div style={styles.infoContainer}>
        <p>Họ và tên: Trần Quốc Qui </p>
        <p>Lớp: 21H40302</p>
        <p>MSSV: 421H0418</p>
        <hr />
        <hr />
        <p>Họ và tên: Nguyễn Thanh Sơn </p>
        <p>Lớp: 21H40302</p>
        <p>MSSV: 421K0051</p>
      </div>
      <Web />
    </div>
  );
}

export default App;